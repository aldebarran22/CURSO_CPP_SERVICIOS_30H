#include "EmpleadoService.h"

EmpleadoService::EmpleadoService(EmpleadoCache& cache, EmpleadoRepository& repositorio):cache(cache), repositorio(repositorio)
{
}

std::optional<Empleado> EmpleadoService::read(int id)
{
	// Buscar en la cache:
	auto emp = this->cache.getEmpleado(id);
	if (emp) {
		// Si está en la cache lo devolvemos
		return emp;
	}
	else {
		// Si no está vamos al repositorio
		emp = this->repositorio.recuperarEmpleado(id);

		if (emp) {
			// Si existe, lo guardamos en la cache:
			this->cache.saveEmpleado(*emp);
		}

		return emp;
	}
}

EmpleadoService::~EmpleadoService()
{
}
