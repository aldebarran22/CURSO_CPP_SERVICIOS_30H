#pragma once
#include "EmpleadoService.h"

class EmpleadoCrow
{
private:
	EmpleadoService& service;

public:
	EmpleadoCrow(EmpleadoService& service);
	void run();
	~EmpleadoCrow();
};

