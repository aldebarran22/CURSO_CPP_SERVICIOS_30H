#include "EmpleadoRepository.hpp"


EmpleadoRepository::EmpleadoRepository(soci::session& sql) : sql_(sql) {}

std::optional<Empleado> EmpleadoRepository::recuperarEmpleado(int id) {
    Empleado emp;
    soci::indicator ind;

    sql_ << "SELECT id, nombre, cargo FROM empleados WHERE id = :id",
        soci::use(id), soci::into(emp.id, ind), soci::into(emp.nombre), soci::into(emp.cargo);

    if (ind == soci::i_null) {
        return std::nullopt;
    }
    return emp;
}

void EmpleadoRepository::insertar(const Empleado& emp) {
    sql_ << "INSERT INTO empleados(id, nombre, cargo) VALUES(:id, :nombre, :cargo)",
        soci::use(emp.id), soci::use(emp.nombre), soci::use(emp.cargo);
}

void EmpleadoRepository::actualizar(const Empleado& emp) {
    sql_ << "UPDATE empleados SET nombre = :nombre, cargo = :cargo WHERE id = :id",
        soci::use(emp.nombre), soci::use(emp.cargo), soci::use(emp.id);
}

void EmpleadoRepository::eliminar(int id) {
    sql_ << "DELETE FROM empleados WHERE id = :id", soci::use(id);
}

std::vector<Empleado> EmpleadoRepository::listarTodos() {
    std::vector<Empleado> empleados;

    soci::rowset<soci::row> rs = sql_.prepare << "SELECT id, nombre, cargo FROM empleados";

    for (const auto& r : rs) {
        Empleado emp;
        emp.id = r.get<int>(0);
        emp.nombre = r.get<std::string>(1);
        emp.cargo = r.get<std::string>(2);
        empleados.push_back(emp);
    }

    return empleados;
}



