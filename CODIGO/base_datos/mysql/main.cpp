// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

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
        std::cerr << "ERROR: " << e.what() << std::endl;
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

        // Operacion DELETE:
        if (repo._delete(10)) {
            std::cout << "Se ha borrado el empleado" << std::endl;
        }
        else {
            std::cout << "No se ha borrado" << std::endl;
        }

        // Operacion CREATE:
        Empleado e{ 10, "Laura", "Comercial" };
        if (repo.create(e)) {
            std::cout << "Se ha creado el empleado" << std::endl;
        }
        else {
            std::cout << "No se ha creado" << std::endl;
        }

        // Operacion UPDATE:
        e.nombre = "Laura Gracia";
        e.cargo = "Representante de ventas";
        if (repo.update(e)) {
            std::cout << "Se ha actualizado el empleado" << std::endl;
        }
        else {
            std::cout << "No se ha actualizado" << std::endl;
        }

        // Operacion SELECT:
        std::cout << "\nListado:\n";
        std::vector<Empleado> empleados = repo.select();
        for (const auto& e : empleados) {
            std::cout << e.nombre << " " << e.cargo << std::endl;
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

