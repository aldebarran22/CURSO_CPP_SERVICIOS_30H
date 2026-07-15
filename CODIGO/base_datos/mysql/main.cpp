// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <optional>

#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"


void testConexion() {
    try {
        soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
        std::cout << "Conexion mysql ok" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void testRepositorio() {
    try {
        soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

        EmpleadoRepositorio repo(sql);

        // Operacion READ:
        int id = 1;

        std::optional<Empleado> emp = repo.read(id);
        if (emp) {
            std::cout << emp->nombre << " " << emp->cargo << std::endl;
        }
        else {
            std::cout << "No existe el empleado con " << id << std::endl;
        }

        // Operacion CREATE:
        Empleado e{ 10, "Laura", "Comercial" };
        if (repo.create(e)) {
            std::cout << "Se ha creado el empleado" << std::endl;
        }
        else {
            std::cout << "No se ha creado" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main()
{
    //testConexion();
    testRepositorio();
}

