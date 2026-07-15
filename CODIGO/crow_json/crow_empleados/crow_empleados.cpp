// crow_empleados.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <optional>

#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"
#include "EmpleadoCache.h"
#include "EmpleadoService.h"
#include "ServicioCrow.h"

int main()
{
    try {
        soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

        EmpleadoRepositorio repo(sql);
        EmpleadoCache cache;
        EmpleadoService service(cache, repo);

        ServicioCrow servicioCrow(service);
        servicioCrow.run();

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
