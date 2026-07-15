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

EmpleadoRepository::~EmpleadoRepository()
{
	PQfinish(this->conn_);
}
