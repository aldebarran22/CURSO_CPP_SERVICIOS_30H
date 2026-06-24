#include "EmpleadoService.h"


EmpleadoService::EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio):cache(cache), repositorio(repositorio)
{
}

std::optional<Empleado> EmpleadoService::read(int id)
{
	auto emp = this->cache.getEmpleado(id);
	if (emp) {
		return emp;
	}
	else {
		emp = this->repositorio.read(id);

		if (emp) {
			this->cache.saveEmpleado(*emp);
		}

		return emp;
	}

}

EmpleadoService::~EmpleadoService()
{
}

