#include <stdexcept>
#include <filesystem>
#include <iostream>

#include "EmpleadoDAO.h"

EmpleadoDAO::EmpleadoDAO(const char* path_file)
{
	this->conexion = nullptr;

	// Primero comprobar si existe el fichero:
	std::filesystem::path archivo(path_file);

	if (!std::filesystem::exists(archivo)) {
		throw std::invalid_argument("Error al abrir la BD, no existe el fichero");
	}

	int rc = sqlite3_open(path_file, &this->conexion);
	if (rc) {
		throw std::invalid_argument("Error al abrir la BD");
	}

	std::cout << "Bd Abierta" << std::endl;
}

bool EmpleadoDAO::create(Empleado *emp)
{
	std::string mensaje;
	sqlite3_stmt* stmt;
	const char* sql = "insert into empleados(nombre, cargo) values(?,?);";

	// Preparar la sentencia:
	int rc = sqlite3_prepare_v2(this->conexion, sql, -1, &stmt, nullptr);
	
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "No se ha podido crear una fila " + std::string(sqlite3_errmsg(this->conexion));		
		throw std::runtime_error(mensaje);
	}

	// Vincular los parametros:
	// Ojo SQLITE_TRANSIENT porque la memoria es volatil y le decimos que copie la mem. inmediatamente
	rc = sqlite3_bind_text(stmt, 1, emp->getNombre().c_str(), -1, SQLITE_TRANSIENT);
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "Error al vincular el parámetro nombre: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	rc = sqlite3_bind_text(stmt, 2, emp->getCargo().c_str(), -1, SQLITE_TRANSIENT);
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "Error al vincular el parámetro cargo: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	// Ejecutar la sentencia:
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		mensaje = "Error al insertar la fila: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	} 

	emp->setId(sqlite3_last_insert_rowid(this->conexion));
	sqlite3_finalize(stmt);
	return true;
}

Empleado EmpleadoDAO::read(int id)
{
	char* errMsg;
	Empleado empleado; // Le pasamos por el 4 parametro de la lambda	
	std::string aux_sql = "select id, nombre, cargo from empleados where id = " + std::to_string(id);
	const char* sql = aux_sql.c_str();

	int rc = sqlite3_exec(this->conexion, sql, [](void* ptr, int argc, char** argv, char** colNames) -> int
		{
			int id;
			std::string nombre, cargo;
			Empleado* emp = static_cast<Empleado*>(ptr);
			
			// El id,pos 0
			id = std::stoi(argv[0]);
			emp->setId(id);

			// El nombre, pos 1
			nombre = argv[1];
			emp->setNombre(nombre);

			// El cargo, pos 2
			cargo = argv[2];
			emp->setCargo(cargo);
			
			return 0;

		}, &empleado, &errMsg); // &empleados entra por el 4 parametro por el void *

	if (rc) {
		throw std::exception(errMsg);
	}
	return empleado;
}

bool EmpleadoDAO::del(int id)
{
	std::string mensaje;
	sqlite3_stmt* stmt;
	const char* sql = "delete from empleados where id = ?";

	// Preparar la sentencia:
	int rc = sqlite3_prepare_v2(this->conexion, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "No se ha podido borrar la fila " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	rc = sqlite3_bind_int(stmt, 1, id);
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "Error al vincular el parámetro id: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	// Ejecutar la sentencia:
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		mensaje = "Error al insertar la fila: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	sqlite3_finalize(stmt);
	int filasAfectadas = sqlite3_changes(this->conexion);
	return filasAfectadas > 0;
}

bool EmpleadoDAO::update(Empleado emp)
{
	std::string mensaje;
	sqlite3_stmt* stmt;
	const char* sql = "update empleados set nombre = ?, cargo = ? where id = ?;";

	// Preparar la sentencia:
	int rc = sqlite3_prepare_v2(this->conexion, sql, -1, &stmt, nullptr);

	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "No se ha podido actualizar la fila " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	// Vincular los parametros:
	// Ojo SQLITE_TRANSIENT porque la memoria es volatil y le decimos que copie la mem. inmediatamente
	rc = sqlite3_bind_text(stmt, 1, emp.getNombre().c_str(), -1, SQLITE_TRANSIENT);
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "Error al vincular el parámetro nombre: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	rc = sqlite3_bind_text(stmt, 2, emp.getCargo().c_str(), -1, SQLITE_TRANSIENT);
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "Error al vincular el parámetro cargo: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	rc = sqlite3_bind_int(stmt, 3, emp.getId());
	if (rc != SQLITE_OK) {
		sqlite3_finalize(stmt);
		mensaje = "Error al vincular el parámetro Id: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	// Ejecutar la sentencia:
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		mensaje = "Error al actualizar la fila: " + std::string(sqlite3_errmsg(this->conexion));
		throw std::runtime_error(mensaje);
	}

	sqlite3_finalize(stmt);
	int filasAfectadas = sqlite3_changes(this->conexion);
	return filasAfectadas > 0;	
}

std::vector<Empleado> EmpleadoDAO::selectAll()
{
	char* errMsg;	
	std::vector<Empleado> empleados; // Le pasamos por el 4 parametro de la lambda	
	const char* sql = "select id, nombre, cargo from empleados order by id;";

	int rc = sqlite3_exec(this->conexion, sql, [](void* ptr, int argc, char** argv, char** colNames) -> int 
		{
			int id;
			std::string nombre, cargo;
			Empleado emp;
			std::vector<Empleado>* empleados = static_cast<std::vector<Empleado> *>(ptr);

			// El id,pos 0
			id = std::stoi(argv[0]);
			emp.setId(id);

			// El nombre, pos 1
			nombre = argv[1];
			emp.setNombre(nombre);

			// El cargo, pos 2
			cargo = argv[2];
			emp.setCargo(cargo);

			empleados->push_back(emp);
			return 0;

		}, &empleados, &errMsg); // &empleados entra por el 4 parametro por el void *

	if (rc) {
		throw std::exception(errMsg);
	}
	return empleados;
}

EmpleadoDAO::~EmpleadoDAO()
{
	if (this->conexion != nullptr) {
		sqlite3_close(this->conexion);
		this->conexion = nullptr;
	}
}


