#pragma once
#include <optional>

#include "EmpleadoCache.h"
#include "EmpleadoRepositorio.h"

class EmpleadoService
{
private:
	EmpleadoCache& cache;
	EmpleadoRepositorio& repositorio;

public:
	EmpleadoService(EmpleadoCache& cache, EmpleadoRepositorio& repositorio);
	std::optional<Empleado> read(int id);
	bool create(const Empleado& e);
	~EmpleadoService();
};
