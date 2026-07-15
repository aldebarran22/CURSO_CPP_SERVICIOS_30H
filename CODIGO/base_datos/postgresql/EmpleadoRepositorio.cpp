#include <stdexcept>

#include "EmpleadoRepositorio.h"


EmpleadoRepository::EmpleadoRepository(const char* cadConex)
{
	this->conn_ = PQconnectdb(cadConex);
	// Comprobar el estado de la conexion:

	if (PQstatus(this->conn_) != CONNECTION_OK) {
		std::string mensaje = PQerrorMessage(this->conn_);
		PQfinish(this->conn_);

		throw std::runtime_error(mensaje);
	}

}

std::vector<Empleado> EmpleadoRepository::listarTodos()
{
	std::vector<Empleado> empleados;
	PGresult* res = PQexec(this->conn_, "select id, nombre, cargo from tbempleados");

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::string mensaje = PQresultErrorMessage(res);
		PQclear(res);
		throw std::runtime_error(mensaje);
	}

	int n = PQntuples(res);
	for (int i = 0; i < n; i++) {
		Empleado emp;
		emp.id = std::stoi(PQgetvalue(res, i, 0));
		emp.nombre = PQgetvalue(res, i, 1);
		emp.cargo = PQgetvalue(res, i, 2);
		empleados.push_back(emp);
	}

	PQclear(res);
	return empleados;
}

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

EmpleadoRepository::~EmpleadoRepository()
{
	PQfinish(this->conn_);
}
