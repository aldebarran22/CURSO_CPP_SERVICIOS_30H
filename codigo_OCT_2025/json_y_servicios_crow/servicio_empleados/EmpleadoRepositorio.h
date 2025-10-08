#pragma once
#include <soci/soci.h>
#include <optional>
#include <vector>
#include "Empleado.h"

class EmpleadoRepositorio
{
private:
	soci::session& sql_;

public:
	EmpleadoRepositorio(soci::session& sql);
	std::optional<Empleado> read(int id);
	void insert(const Empleado& e);
	void update(const Empleado& e);
	void delete_(int id);
	std::vector<Empleado> select();
};

