// crow_bd_cache.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <memory>
#include <cstdlib>
#include <string>
#include <mysql/mysql.h>

#include "PedidoRepositorio.h"
#include "PedidoCache.h"
#include "PedidoService.h"
#include "PedidoCROW.h"

MYSQL* crearConexionMySQL()
{
    // Leer variables de entorno (Docker)
    const char* envHost = std::getenv("MYSQL_HOST");
    const char* envUser = std::getenv("MYSQL_USER");
    const char* envPass = std::getenv("MYSQL_PASSWORD");
    const char* envDB   = std::getenv("MYSQL_DB");
    const char* envPort = std::getenv("MYSQL_PORT");

    // Valores por defecto (Visual Studio)
    std::string host = envHost ? envHost : "127.0.0.1";
    std::string user = envUser ? envUser : "root";
    std::string pass = envPass ? envPass : "antonio";
    std::string db   = envDB   ? envDB   : "empresa3";
    int port         = envPort ? std::stoi(envPort) : 3307;

    std::cout << "Conectando a MySQL en " << host << ":" << port << std::endl;

    MYSQL* conn = mysql_init(nullptr);
    if (!conn) {
        throw std::runtime_error("mysql_init() failed");
    }

    if (!mysql_real_connect(conn,
                            host.c_str(),
                            user.c_str(),
                            pass.c_str(),
                            db.c_str(),
                            port,
                            nullptr,
                            0))
    {
        std::string err = mysql_error(conn);
        throw std::runtime_error("Error conectando a MySQL: " + err);
    }

    return conn;
}

int main()
{
    try {
        // Crear conexión MySQL (Docker o Visual Studio)
        MYSQL* conn = crearConexionMySQL();

        // Crear el repositorio e inyectar la conexión
        auto repositorio = std::make_shared<PedidoRepositorio>(conn);

        // Crear la cache
        auto cache = std::make_shared<PedidoCache>();

        // Crear el servicio (lógica de negocio)
        auto service = std::make_shared<PedidoService>(cache, repositorio);

        // Crear el servicio Crow e inyectar service
        PedidoCROW servicioCrow(service);
        servicioCrow.run();

        mysql_close(conn);
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}
