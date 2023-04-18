FROM alpine:3.17.3 AS build

RUN apk update && \
    apk add --no-cache \
    build-base=0.5-r3 \
    cmake=3.24.4-r0
    
WORKDIR /journal

COPY src/ ./src/
COPY CMakeLists.txt .

WORKDIR /journal/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --parallel 8 && \
    mkdir ../bin && \
    mv journal-cli ../bin/journal-cli

FROM alpine:3.17.3 

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S shs && adduser -S shs -G shs
USER shs

COPY --chown=shs:shs --from=build \
    ./journal/bin/journal-cli \
    ./app/journal-cli

ENTRYPOINT [ "./app/journal-cli" ]
