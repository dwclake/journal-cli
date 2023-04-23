# Start with a base alpine image
FROM alpine:3.17.3 AS build

# Install build tools and cmake
RUN apk update && \
    apk add --no-cache \
    build-base=0.5-r3 \
    cmake=3.24.4-r0
    
# Set the working directory
WORKDIR /journal

# Copy the project files
COPY source/ ./source/
COPY include/ ./include/
COPY test/ ./test/
COPY CMakeLists.txt .

# Build the project with cmake and move the binary to the bin directory
RUN cmake -DCMAKE_BUILD_TYPE=Release -B build -S . && \
    cmake --build build --parallel 8 && \
    mkdir bin && \
    mv build/journal-cli bin/journal-cli

# Start with a base alpine image
FROM alpine:3.17.3 

# Install libstdc++
RUN apk update && \
    apk add --no-cache \
    libstdc++

# create a user and group
RUN addgroup -S shs && adduser -S shs -G shs
USER shs

# Copy the binary from the build stage
COPY --chown=shs:shs --from=build \
    ./journal/bin/journal-cli \
    ./app/journal-cli

# Set the entrypoint
ENTRYPOINT [ "./app/journal-cli" ]
