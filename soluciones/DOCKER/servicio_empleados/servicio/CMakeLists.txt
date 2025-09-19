cmake_minimum_required(VERSION 3.30)
project(microservicio-empleados)

# Activar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Usar vcpkg como toolchain
# Esto se define en el comando de cmake, este comando va al Dockerfile
# cmake -DCMAKE_TOOLCHAIN_FILE=/opt/vcpkg/scripts/buildsystems/vcpkg.cmake

# Añadir los ficheros del codigo fuente:
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(microservicio ${SOURCES})

# Buscar las librerias instaladas por vcpkg
find_package(Crow CONFIG REQUIRED)
find_package(soci CONFIG REQUIRED)
find_package(hiredis CONFIG REQUIRED)

# Enlazar las librerias al ejecutable:
target_link_libraries(microservicio PRIVATE	
	soci_core
	soci_mysql
	Crow::Crow
	hiredis::hiredis
)