cmake_minimum_required(VERSION 3.15)
project(practica4crow LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crow es header-only, no necesita find_package
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
        OpenSSL::SSL
        OpenSSL::Crypto
)
