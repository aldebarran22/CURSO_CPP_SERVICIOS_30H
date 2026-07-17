# Stage 1: Build (para generar el binario)
FROM ubuntu:22.04 AS builder

# Instalar librerias y herramientas:
RUN apt-get update && apt-get install -y \
    git cmake g++ build-essential \
    libboost-all-dev \
    libssl-dev \
    libasio-dev

# Clonar el repositorio de crow:
RUN git clone https://github.com/CrowCpp/Crow.git /crow

# Establecer la carpeta de trabajo: y ya nos situa dentro de la carpeta
WORKDIR /src

# Copiar el contenido del host a la imagen
COPY . .

# Compilar:
RUN cmake -B build -S . -DMAKE_BUILD_TYPE=Release

RUN cmake --build build --config Release

########################################

# Stage 2: Runtime (para ejecutar el servicio)
FROM ubuntu:22.04
