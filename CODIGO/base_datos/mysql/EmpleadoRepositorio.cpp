#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session& sql)
{
}

std::optional<Empleado> EmpleadoRepositorio::read(int id)
{
	return std::optional<Empleado>();
}

bool EmpleadoRepositorio::create(const Empleado& emp)
{
	return false;
}

bool EmpleadoRepositorio::_delete(int id)
{
	return false;
}

bool EmpleadoRepositorio::update(const Empleado& emp)
{
	return false;
}

std::vector<Empleado> EmpleadoRepositorio::select()
{
	return std::vector<Empleado>();
}

EmpleadoRepositorio::~EmpleadoRepositorio()
{
}
