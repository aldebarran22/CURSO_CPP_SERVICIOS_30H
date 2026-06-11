#pragma once
#include "EmpleadoService.h"

class EmpleadoCROW
{
public:
	EmpleadoCROW(EmpleadoService&);
	void run();
	~EmpleadoCROW();

private:
	EmpleadoService& service;
};

