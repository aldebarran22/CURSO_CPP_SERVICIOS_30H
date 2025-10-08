#include "EmpleadoService.h"

EmpleadoService::EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio):cache(cache), repositorio(repositorio)
{
}

std::optional<Empleado> EmpleadoService::obtenerEmpleado(int id)
{
	// Primero buscamos en la cache:
	auto emp = cache.getEmpleado(id);

	if (emp)
		return emp;

	else {
		// Tenemos que ir al repositorio a buscarlo:
		emp = repositorio.read(id);

		if (emp)
			// Si lo hemos encontrado lo guardamos en la cache:
			cache.saveEmpleado(*emp);

		return emp;
	}

	return std::optional<Empleado>();
}

EmpleadoService::~EmpleadoService()
{
}
