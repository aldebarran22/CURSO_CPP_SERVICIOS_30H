# Imagen base
FROM ubuntu:20.04

# Evitar interacción en la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instalar herramientas necesarias: libssl-dev es para crow por si establece conexiones seguras
# libmysqlclient-dev: es el cliente de mysql

RUN apt-get update && apt-get install -y \
    g++ git curl zip unzip tar make pkg-config libssl-dev libmysqlclient-dev \
    && rm -rf /var/lib/apt/lists/*
	
# Instalar CMake 3.30 manualmente
WORKDIR /tmp
RUN curl -LO https://github.com/Kitware/CMake/releases/download/v3.30.0/cmake-3.30.0-linux-x86_64.sh && \
    chmod +x cmake-3.30.0-linux-x86_64.sh && \
    ./cmake-3.30.0-linux-x86_64.sh --skip-license --prefix=/usr/local

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
RUN vcpkg install && \
    /opt/vcpkg/vcpkg remove soci && \
    /opt/vcpkg/vcpkg install soci[mysql]



# Compilar el proyecto
RUN cmake -Bbuild -S. -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    cmake --build build

# Exponer el puerto del microservicio
EXPOSE 8000

# Ejecutar el binario
CMD ["./build/microservicio"]
