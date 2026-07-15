#pragma once

#include "EmpleadoService.h"

class ServicioCrow
{

private:
	EmpleadoService& service;

public:
	ServicioCrow(EmpleadoService& service);
	void run();
	~ServicioCrow();
};

