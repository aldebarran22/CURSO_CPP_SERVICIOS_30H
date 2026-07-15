#pragma once

#include <optional>
#include <hiredis/hiredis.h>

#include "Empleado.h"

class EmpleadoCache
{
private:
	redisContext* contexto;

public:
	EmpleadoCache();
	std::optional<Empleado> getEmpleado(int id);
	void saveEmpleado(const Empleado& e);
	~EmpleadoCache();
};

