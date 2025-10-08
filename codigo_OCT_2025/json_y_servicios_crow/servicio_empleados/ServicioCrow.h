#pragma once
#include "EmpleadoService.h"

class ServicioCrow
{
private:
	EmpleadoService& service;

public:
	ServicioCrow(EmpleadoService&);
	void iniciar();
	~ServicioCrow();
};

