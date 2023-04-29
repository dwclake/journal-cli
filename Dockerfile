ARG test=false

# Start with a base alpine image
FROM alpine:3.17.3 AS build

# Install build tools and cmake
RUN apk update && \
    apk add --no-cache \
    git \
    curl \
    zip \
    unzip \
    tar \
    g++ \ 
    py3-pip \
    pkgconfig \
    make

RUN pip install cmake ninja
    
# Set the working directory
WORKDIR /journal

# Copy the project files
COPY .git/ ./.git/
COPY source/ ./source/
COPY include/ ./include/
COPY test/ ./test/
COPY vcpkg.json .
COPY .gitmodules .
COPY CMakeLists.txt .

RUN git submodule init
RUN git submodule update
RUN ./vcpkg/bootstrap-vcpkg.sh

RUN ./vcpkg/vcpkg install

# Build the project with cmake and move the binary to the bin directory
RUN cmake -DCMAKE_BUILD_TYPE=Release -B build -S . \
    "-DCMAKE_TOOLCHAIN_FILE=/journal/vcpkg/scripts/buildsystems/vcpkg.cmake" && \
    cmake --build build --parallel 8 && \
    mkdir bin && \
    mv build/journal-cli bin/journal-cli && \
    mv build/journal-cli-test bin/journal-cli-test

# Start with a base alpine image
FROM alpine:3.17.3 

# Install libstdc++
RUN apk update && \
    apk add --no-cache \
    libstdc++ \
    py3-pip

RUN pip install cmake

# create a user and group
RUN addgroup -S shs && adduser -S shs -G shs
USER shs

# Copy the binary from the build stage
COPY --chown=shs:shs --from=build \
    ./journal/bin/* \
    ./app

# Set the entrypoint
ENTRYPOINT [ "./app/journal-cli" ]
