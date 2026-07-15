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
	soci::statement st = (sql.prepare << "insert into empleados values(:id, :nombre, :cargo)",
		soci::use(emp.id), soci::use(emp.nombre), soci::use(emp.cargo));
	st.execute(true);
	return st.get_affected_rows() == 1;
}

bool EmpleadoRepositorio::_delete(int id)
{
	soci::statement st = (sql.prepare << "delete from empleados where id=:id", soci::use(id));
	st.execute(true);
	return st.get_affected_rows() == 1;
}

bool EmpleadoRepositorio::update(const Empleado& emp)
{
	soci::statement st = (sql.prepare << "update empleados set nombre=:nombre, cargo=:cargo where id=:id", 
		soci::use(emp.nombre), soci::use(emp.cargo), soci::use(emp.id));
	st.execute(true);
	return st.get_affected_rows() == 1;
}

std::vector<Empleado> EmpleadoRepositorio::select()
{
	std::vector<Empleado> empleados;
	soci::rowset<soci::row> rs = sql.prepare << "select id, nombre, cargo from empleados";

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
