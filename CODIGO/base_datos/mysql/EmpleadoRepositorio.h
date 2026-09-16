#pragma once

#include <soci/soci.h>
#include <vector>
#include <optional>

#include "Empleado.h"

class EmpleadoRepositorio
{
private:
	soci::session& sql;

public:
	EmpleadoRepositorio(soci::session& sql);
	std::optional<Empleado> read(int id);
	bool create(const Empleado& emp);
	bool _delete(int id);
	bool update(const Empleado& emp);
	std::vector<Empleado> select();
	~EmpleadoRepositorio();
};

