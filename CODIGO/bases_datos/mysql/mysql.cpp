// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <optional>
#include <vector>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"
#include "EmpleadoCache.h"
#include "EmpleadoService.h"


void testRepositorio() {
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
    EmpleadoRepositorio repo(sql);

    if (repo._delete(10)) {
        std::cout << "empleado borrado\n";
    }

    // Crear un empleado:
    Empleado e{ 10, "Laura", "Comercial" };
    if (repo.create(e)) {
        std::cout << "empleado creado\n";
    }

    // Recuperar:
    std::optional<Empleado> emp = repo.read(10);
    if (emp) {
        std::cout << emp->nombre << " " << emp->cargo << std::endl;
    }
    else {
        std::cout << "No existe el empleado" << std::endl;
    }

    e.nombre = "Laura Gomez";
    e.cargo = "Analista";

    if (repo.update(e)) {
        std::cout << "empleado actualizado\n";
    }

    std::cout << "Listado:\n";
    std::vector<Empleado> empleados = repo.select();
    for (const auto& e : empleados) {
        std::cout << e.nombre << " " << e.cargo << std::endl;
    }
}

void testCache() {
    EmpleadoCache cache;
    Empleado e{ 1, "Juan", "Gerente" };

    //cache.saveEmpleado(e);

    auto e2 = cache.getEmpleado(2);
    if (e2.has_value()) {
        std::cout << e2->nombre << " " << e2->cargo << std::endl;
    }
    else {
        std::cout << "No existe en la cache" << std::endl;
    }
}

void testService() {
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
    EmpleadoRepositorio repo(sql);

    EmpleadoCache cache;
    EmpleadoService service(cache, repo);

    auto e2 = service.read(7);
    if (e2.has_value()) {
        std::cout << e2->nombre << " " << e2->cargo << std::endl;
    }
    else {
        std::cout << "No existe en la BD de mysql" << std::endl;
    }
}

int main()
{
    //testRepositorio();
    //testCache();
    testService();
}

