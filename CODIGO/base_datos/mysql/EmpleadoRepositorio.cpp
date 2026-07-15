#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session& sql):sql(sql)
{
}

std::optional<Empleado> EmpleadoRepositorio::read(int id)
{
	Empleado emp;
	soci::indicator ind;

	sql << "select id, nombre, cargo from empleados where id = :id", soci::use(id),
		soci::into(emp.id, ind), soci::into(emp.nombre), soci::into(emp.cargo);

	if (ind == soci::i_null) {
		return std::nullopt;
	}
	else {
		return emp;
	}
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
