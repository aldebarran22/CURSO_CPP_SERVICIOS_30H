#pragma once
#include <optional>

#include "Empleado.h"
#include "EmpleadoCache.h"
#include "EmpleadoRepositorio.h"

class EmpleadoService
{
private:
	EmpleadoCache& cache;
	EmpleadoRepositorio& repositorio;

public:
	EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio);
	std::optional<Empleado> obtenerEmpleado(int id);
	~EmpleadoService();
};

