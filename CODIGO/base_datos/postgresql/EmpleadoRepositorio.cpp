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

EmpleadoRepository::~EmpleadoRepository()
{
	PQfinish(this->conn_);
}
