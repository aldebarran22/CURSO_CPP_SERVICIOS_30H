// servicio_empleados.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"

void testRepositorio() {
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
    EmpleadoRepositorio repo(sql);

    // Recuperar un empleado:
    
    auto emp = repo.read(1);
    if (emp) {
        std::cout << emp->nombre << " " << emp->cargo << std::endl;
    }
    else {
        std::cerr << "No se encontro el empleado ... " << std::endl;
    }

    for (const auto& emp : repo.select()) {
        std::cout << emp.id << " " << emp.nombre << " " << emp.cargo << std::endl;
    }
}

int main()
{
    testRepositorio();
    return 0;
}

