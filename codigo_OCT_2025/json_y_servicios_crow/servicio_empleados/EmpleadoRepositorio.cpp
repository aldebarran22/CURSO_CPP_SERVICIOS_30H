#include "EmpleadoRepositorio.h"

EmpleadoRepositorio::EmpleadoRepositorio(soci::session& sql):sql_(sql)
{
}

std::optional<Empleado> EmpleadoRepositorio::read(int id)
{
	Empleado emp;
	soci::indicator ind;

	sql_ << "select id, nombre, cargo from empleados where id = :id", soci::use(id),
		soci::into(emp), soci::into(emp.id, ind), soci::into(emp.nombre), soci::into(emp.cargo);

	if (ind == soci::i_null)
		return std::nullopt;
	else
		return emp;
}

void EmpleadoRepositorio::insert(const Empleado& e)
{
	sql_ << "insert into empleado(id, nombre, cargo) values(:id, :nombre, :cargo)",
		soci::use(e.id), soci::use(e.nombre), soci::use(e.cargo);
}

void EmpleadoRepositorio::update(const Empleado& e)
{
	sql_ << "UPDATE empleados SET nombre = :nombre, cargo = :cargo WHERE id = :id",
		soci::use(e.nombre), soci::use(e.cargo), soci::use(e.id);
}

void EmpleadoRepositorio::delete_(int id)
{
	sql_ << "DELETE FROM empleados WHERE id = :id", soci::use(id);
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
