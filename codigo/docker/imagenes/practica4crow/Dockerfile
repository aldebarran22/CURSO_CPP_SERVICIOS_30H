# ============================
# Stage 1: Build
# ============================
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    git cmake g++ build-essential \
    libboost-all-dev \
    libssl-dev \
    libasio-dev

# Clonar Crow (header-only)
RUN git clone https://github.com/CrowCpp/Crow.git /crow

WORKDIR /src
COPY . .

# Compilar
RUN cmake -B build -S . \
    -DCMAKE_BUILD_TYPE=Release

RUN cmake --build build --config Release


# ============================
# Stage 2: Runtime
# ============================
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
    libboost-system1.74.0 \
    libboost-thread1.74.0 \
    libssl3 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /src/build/practica4crow .

EXPOSE 8080
CMD ["./practica4crow"]
