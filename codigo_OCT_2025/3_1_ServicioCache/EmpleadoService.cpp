#include "EmpleadoService.hpp"

EmpleadoService::EmpleadoService(EmpleadoCache& cache, EmpleadoRepository& repositorio):cache(cache), repositorio(repositorio)
{
	// En la lista de iniciadores inyecta los dos objetos: redis para la cache, y el repositorio para mysql
}

std::optional<Empleado> EmpleadoService::obtenerEmpleado(int id)
{
	// Primero buscamos en la cache:
	auto emp = this->cache.getEmpleado(id);

	if (emp) {
		return emp;

	} else {
		// Hay que ir a buscar al repositorio:
		emp = this->repositorio.recuperarEmpleado(id);

		if (emp) {
			// Guardar el empleado en la cache:
			this->cache.saveEmpleado(*emp);
		}

		return emp;
	}
}

EmpleadoService::~EmpleadoService()
{
}
