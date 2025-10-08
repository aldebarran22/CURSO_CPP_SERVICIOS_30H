#pragma once

#include "EmpleadoService.hpp"

class MicroServicioCROW
{
private:
	EmpleadoService& service;

public:
	MicroServicioCROW(EmpleadoService&);
	void iniciar();
	~MicroServicioCROW();
};

