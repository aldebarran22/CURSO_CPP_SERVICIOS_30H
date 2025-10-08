#pragma once

#include <optional>

#include "Empleado.hpp"
#include "EmpleadoCache.hpp"
#include "EmpleadoRepository.hpp"

class EmpleadoService
{
public:
	EmpleadoService(EmpleadoCache& cache, EmpleadoRepository &repositorio);
	std::optional<Empleado> obtenerEmpleado(int id);
	~EmpleadoService();

private:
	EmpleadoCache& cache;
	EmpleadoRepository& repositorio;
};

