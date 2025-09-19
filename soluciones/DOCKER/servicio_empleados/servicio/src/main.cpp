#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <iostream>

#include "EmpleadoCache.hpp"
#include "EmpleadoRepository.hpp"
#include "EmpleadoService.hpp"
#include "MicroServicioCROW.hpp"


int main() {
	
	std::cout << "API para la recuperacion de empleados de la BD con un sistema de Cache con Redis" << std::endl;

	// Crear la cache y el repositorio:
	EmpleadoCache cache;
	soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
	EmpleadoRepository repositorio(sql);

	// El Service: Logica de negocio:
	EmpleadoService service(cache, repositorio);

	// El microservicio:
	MicroServicioCROW microservicio(service);
	microservicio.iniciar();

	return 0;
}