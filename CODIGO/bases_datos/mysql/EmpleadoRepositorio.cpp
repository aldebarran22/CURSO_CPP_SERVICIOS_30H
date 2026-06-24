#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session& sql):sql_(sql)
{
}

std::optional<Empleado> EmpleadoRepositorio::read(int id)
{
	Empleado emp;
	soci::indicator ind;

	sql_ << "select id, nombre, cargo from empleados where id = :id",
		soci::use(id), soci::into(emp.id, ind), soci::into(emp.nombre), soci::into(emp.cargo);

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
	std::vector<Empleado> empleados;
	soci::rowset<soci::row> rs = sql_.prepare << "select id, nombre, cargo from empleados";

	for (const auto& r : rs) {
		Empleado e;
		e.id = r.get<int>(0);
		e.nombre = r.get<std::string>(1);
		e.cargo = r.get<std::string>(2);

		empleados.push_back(e);
	}

	return empleados;
}

EmpleadoRepositorio::~EmpleadoRepositorio()
{
}
