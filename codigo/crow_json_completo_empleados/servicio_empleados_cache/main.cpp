// servicio_empleados.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "EmpleadoRepositorio.h"
#include "EmpleadoService.h"
#include "EmpleadoCROW.h"
#include "EmpleadoCache.h"

void arrancarServicio() {
    // Crear la session de soci:
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

    // Crear un repositorio:
    EmpleadoRepository repo(sql);

    // Crear la cache:
    EmpleadoCache cache;

    EmpleadoService service(cache, repo);

    // Crear el servicio y ponerlo en marcha:
    EmpleadoCROW servicio(service);
    servicio.run();
}

void testEmpleadoCache() {
    EmpleadoCache cache;
    Empleado emp = { 1, "Juan", "Gerente" };

    std::cout << emp.to_string() << std::endl;
    cache.saveEmpleado(emp);

    auto emp2 = cache.getEmpleado(1);
    if (emp2.has_value()) {
        std::cout << emp2->to_string() << std::endl;
    }
    else {
        std::cout << "No se ha podido recuperar" << std::endl;
    }
}


int main()
{
    arrancarServicio();
    //testEmpleadoCache();
    return 0;
}

