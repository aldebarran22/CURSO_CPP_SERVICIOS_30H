#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session& sql)
{
}

void EmpleadoRepositorio::insert(const Empleado& e)
{
}

void EmpleadoRepositorio::update(const Empleado& e)
{
}

void EmpleadoRepositorio::delete_(int id)
{
}

std::vector<Empleado> EmpleadoRepositorio::select()
{
	return std::vector<Empleado>();
}
