FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add --no-cache \
    build-base=0.5-r3 \
    cmake=3.24.3-r0

WORKDIR /diary

COPY includes/ ./includes/
COPY main.cpp .
COPY CMakeLists.txt .

WORKDIR /diary/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --parallel 8

FROM alpine:3.17.0 

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S shs && adduser -S shs -G shs
USER shs

COPY --chown=shs:shs --from=build \
    ./diary/build \
    ./app/

ENTRYPOINT [ "./app/diary-cli" ]
