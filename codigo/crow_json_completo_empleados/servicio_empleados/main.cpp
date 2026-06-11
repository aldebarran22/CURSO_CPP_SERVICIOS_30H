// servicio_empleados.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "EmpleadoRepositorio.h"
#include "EmpleadoCROW.h"

int main()
{
    // Crear la session de soci:
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

    // Crear un repositorio:
    EmpleadoRepository repo(sql);

    // Crear el servicio y ponerlo en marcha:
    EmpleadoCROW servicio(repo);
    servicio.run();

}

