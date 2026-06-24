#pragma once

#include <soci/soci.h>
#include <optional>
#include <vector>
#include "Empleado.h"

class EmpleadoRepositorio
{
public:
	EmpleadoRepositorio(soci::session& sql);
	std::optional<Empleado> read(int id);
	bool create(const Empleado& emp);
	bool _delete(int id);
	bool update(const Empleado& emp);
	std::vector<Empleado> select();
	~EmpleadoRepositorio();

private:
	soci::session& sql_;
};

