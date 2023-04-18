FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add --no-cache \
    build-base=0.5-r3 \
    cmake

WORKDIR /journal

COPY includes/ ./includes/
COPY main.cpp .
COPY CMakeLists.txt .

WORKDIR /journal/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --parallel 8

FROM alpine:3.17.0 

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S shs && adduser -S shs -G shs
USER shs

COPY --chown=shs:shs --from=build \
    ./journal/build/journal-cli \
    ./app/journal-cli

ENTRYPOINT [ "./app/journal-cli" ]
