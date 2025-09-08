#pragma once

#include <vector>
#include "Empleado.h"

class IEmpleadoDAO {

public:
	virtual bool create(Empleado *) = 0;
	virtual Empleado read(int) = 0;
	virtual bool del(int) = 0;
	virtual bool update(Empleado) = 0;
	virtual std::vector<Empleado> selectAll() = 0;
};

