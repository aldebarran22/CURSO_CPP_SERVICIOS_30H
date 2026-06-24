// crow_empleados.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"
#include "EmpleadoCache.h"
#include "EmpleadoService.h"
#include "EmpleadoCrow.h"


int main()
{
	// Crear la sesion:
	soci::session sql(soci::mysql, "db=empresa3 user=root password=antonio host=127.0.0.1 port=3307");

    // Crear el repositorio:
	EmpleadoRepositorio repo(sql);

	// Crear la cache:
	EmpleadoCache cache;

	// Crear el service:
	EmpleadoService service(cache, repo);

	EmpleadoCrow servicio(service);
	servicio.run();
}
