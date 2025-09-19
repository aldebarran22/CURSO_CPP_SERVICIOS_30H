# Imagen base
FROM ubuntu:20.04

# Evitar interacción en la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instalar herramientas necesarias: libssl-dev es para crow por si establece conexiones seguras
# libmysqlclient-dev: es el cliente de mysql

RUN apt-get update && apt-get install -y \
    g++ cmake git curl libssl-dev libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*

# Instalar vcpkg
WORKDIR /opt
RUN git clone https://github.com/microsoft/vcpkg.git && \
    ./vcpkg/bootstrap-vcpkg.sh

ENV VCPKG_ROOT=/opt/vcpkg
ENV PATH="$VCPKG_ROOT:$PATH"

# Crear directorio de trabajo
WORKDIR /app

# Copiar archivos del proyecto
COPY ./src ./src
COPY CMakeLists.txt .
COPY vcpkg.json .

# Instalar dependencias con vcpkg
RUN vcpkg install

# Compilar el proyecto
RUN cmake -Bbuild -S. -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    cmake --build build

# Exponer el puerto del microservicio
EXPOSE 8000

# Ejecutar el binario
CMD ["./build/microservicio"]
