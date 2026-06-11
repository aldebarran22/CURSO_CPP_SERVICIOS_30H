#pragma once

#include "EmpleadoCache.h"
#include "EmpleadoRepositorio.h"

#include <optional>

class EmpleadoService
{
private:
	EmpleadoCache& cache;
	EmpleadoRepository& repositorio;

public:
	EmpleadoService(EmpleadoCache&, EmpleadoRepository&);
	std::optional<Empleado> read(int);
	~EmpleadoService();
};

