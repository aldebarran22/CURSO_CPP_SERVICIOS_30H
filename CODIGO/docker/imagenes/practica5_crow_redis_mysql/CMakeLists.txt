cmake_minimum_required(VERSION 3.16)
project(pedidos_crow)

set(CMAKE_CXX_STANDARD 17)

# Crow (header-only)
include_directories(/crow/include)

# MySQL client
find_library(MYSQL_LIB mysqlclient REQUIRED)
find_library(HIREDIS_LIB hiredis REQUIRED)

add_executable(pedidos
    main.cpp
    Pedido.cpp
    PedidoRepositorio.cpp
    PedidoCache.cpp
    PedidoService.cpp
    PedidoCROW.cpp
    utilidades.cpp
)

target_link_libraries(pedidos
    PRIVATE
        ${MYSQL_LIB}
        ${HIREDIS_LIB}
        pthread
)
