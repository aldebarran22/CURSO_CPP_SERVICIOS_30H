#pragma once
#include "EmpleadoRepositorio.h"

class EmpleadoCROW
{
public:
	EmpleadoCROW(EmpleadoRepository&);
	void run();
	~EmpleadoCROW();

private:
	EmpleadoRepository& repositorio;
};

