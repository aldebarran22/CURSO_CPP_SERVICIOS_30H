# Especificar la version del comando cmake:
cmake_minimum_required(VERSION 3.15)

# Nombre del proyecto y el lenguaje
project(practica4crow LANGUAGES CXX)

# Version de Cpp
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# De crow donde estan los ficheros .h
include_directories(/crow/include)

find_package(Boost REQUIRED COMPONENTS system thread)
find_package(OpenSSL REQUIRED)

add_executable(practica4crow
	practica4crow.cpp
	CrowCRUD.cpp
)

target_link_libraries(practica4crow
   PRIVATE
      Boost::system
      Boost::thread
      OpenSSL:SSL
      OpenSSL::Crypto
)

