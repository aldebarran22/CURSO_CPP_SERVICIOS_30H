#include "EmpleadoService.h"

EmpleadoService::EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio):cache(cache), repositorio(repositorio)
{
}

std::optional<Empleado> EmpleadoService::read(int id)
{
	// 1) Buscarlo en la cache:
	auto emp = this->cache.getEmpleado(id);

	if (emp) {
		// Si existe se devuelve
		return emp;
	}
	else {
		// Si no existe, ir al repositorio
		emp = this->repositorio.read(id);

		if (emp) {
			// Si existe en el repositorio, se guarda tambien en la cache
			this->cache.saveEmpleado(*emp);
		}
		return emp;
	}
}


bool EmpleadoService::create(const Empleado& e)
{
	// Se crea en el repositorio y se guarda en la cache
	bool ok = this->repositorio.create(e);

	if (ok) {
		this->cache.saveEmpleado(e);
	}

	return ok;
}


EmpleadoService::~EmpleadoService()
{
}

