#include "EmpleadoRepository.hpp"
#include <stdexcept>
#include <iostream>

EmpleadoRepository::EmpleadoRepository(PGconn* conn) : conn_(conn) {}

std::optional<Empleado> EmpleadoRepository::recuperarEmpleado(int id) {
    std::string query = "SELECT id, nombre, cargo FROM tbempleados WHERE id = " + std::to_string(id);
    PGresult* res = PQexec(conn_, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        throw std::runtime_error("Error al recuperar empleado");
    }

    if (PQntuples(res) == 0) {
        PQclear(res);
        return std::nullopt;
    }

    Empleado emp;
    emp.id = std::stoi(PQgetvalue(res, 0, 0));
    emp.nombre = PQgetvalue(res, 0, 1);
    emp.cargo = PQgetvalue(res, 0, 2);

    PQclear(res);
    return emp;
}

void EmpleadoRepository::insertar(const Empleado& emp) {
    std::string query = "INSERT INTO tbempleados(id, nombre, cargo) VALUES("+std::to_string(emp.id)+", '" +
        emp.nombre + "', '" + emp.cargo + "')";
    PGresult* res = PQexec(conn_, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw std::runtime_error("Error al insertar empleado");
    }

    PQclear(res);
}

/* OJO sin parametrizar --> SQL Inyection!

void EmpleadoRepository::actualizar(const Empleado& emp) {
    std::string query = "UPDATE tbempleados SET nombre = '" + emp.nombre +
        "', cargo = '" + emp.cargo + "' WHERE id = " + std::to_string(emp.id);
    PGresult* res = PQexec(conn_, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw std::runtime_error("Error al actualizar empleado");
    }

    PQclear(res);
}*/

void EmpleadoRepository::actualizar(const Empleado& emp) {
    const char* query = "UPDATE tbempleados SET nombre = $1, cargo = $2 WHERE id = $3";

    const char* paramValues[3];
    paramValues[0] = emp.nombre.c_str();
    paramValues[1] = emp.cargo.c_str();
    std::string idStr = std::to_string(emp.id);
    paramValues[2] = idStr.c_str();

    PGresult* res = PQexecParams(
        conn_,
        query,
        3,              // número de parámetros
        nullptr,        // tipos de parámetros (NULL = inferidos)
        paramValues,    // valores
        nullptr,        // longitudes (NULL para texto)
        nullptr,        // formatos (NULL = texto)
        0               // resultado en texto (0) o binario (1)
    );

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::string errorMsg = PQerrorMessage(conn_);
        PQclear(res);
        throw std::runtime_error("Error al actualizar empleado: " + errorMsg);
    }

    PQclear(res);
}


void EmpleadoRepository::eliminar(int id) {
    std::string query = "DELETE FROM tbempleados WHERE id = " + std::to_string(id);
    PGresult* res = PQexec(conn_, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        PQclear(res);
        throw std::runtime_error("Error al eliminar empleado");
    }

    PQclear(res);
}

std::vector<Empleado> EmpleadoRepository::listarTodos() {
    std::vector<Empleado> empleados;
    PGresult* res = PQexec(conn_, "SELECT id, nombre, cargo FROM tbempleados");

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        PQclear(res);
        throw std::runtime_error("Error al listar empleados");
    }

    int rows = PQntuples(res);
    for (int i = 0; i < rows; ++i) {
        Empleado emp;
        emp.id = std::stoi(PQgetvalue(res, i, 0));
        emp.nombre = PQgetvalue(res, i, 1);
        emp.cargo = PQgetvalue(res, i, 2);
        empleados.push_back(emp);
    }

    PQclear(res);
    return empleados;
}

