#pragma once

#include "EmpleadoCache.h"
#include "EmpleadoRepositorio.h"

#include <optional>

class EmpleadoService
{
private:
	EmpleadoCache& cache;
	EmpleadoRepositorio& repositorio;

public:
	EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio);
	std::optional<Empleado> read(int id);
	~EmpleadoService();
};

