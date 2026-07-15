// postgresql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <libpq-fe.h>
#include <iostream>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"

int main()
{
    try {
        const char* cadConex = "host=127.0.0.1 port=5433 dbname=empresa user=antonio password=antonio";
        EmpleadoRepository repo(cadConex);
        std::cout << "Conexion ok" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

