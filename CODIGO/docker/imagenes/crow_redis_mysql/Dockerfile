FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    git g++ build-essential cmake \
    libmysqlclient-dev \
    libhiredis-dev \
    libssl-dev \
    nlohmann-json3-dev \
    libasio-dev \
    curl unzip

RUN git clone https://github.com/CrowCpp/Crow.git /crow

WORKDIR /src
COPY . .

RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --config Release


FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libmysqlclient21 \
    libhiredis0.14 \
    libssl3 \
    nlohmann-json3-dev \   
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /src/build/pedidos .

EXPOSE 8082
CMD ["./pedidos"]
