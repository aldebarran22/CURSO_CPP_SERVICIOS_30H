#include <stdexcept>
#include "EmpleadoDAOMySQL.h"

EmpleadoDAOMySQL::EmpleadoDAOMySQL(const char* path)
{
}

bool EmpleadoDAOMySQL::create(Empleado*)
{
	return false;
}

Empleado EmpleadoDAOMySQL::read(int)
{
	return Empleado();
}

bool EmpleadoDAOMySQL::del(int)
{
	return false;
}

bool EmpleadoDAOMySQL::update(Empleado emp) {
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[3];
    const char* sql = "UPDATE empleados SET nombre = ?, cargo = ? WHERE id = ?";

    stmt = mysql_stmt_init(this->conexion);
    if (!stmt) {
        throw std::runtime_error("Error al inicializar la sentencia");
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        std::string mensaje = "Error al preparar la sentencia: " + std::string(mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        throw std::runtime_error(mensaje);
    }

    memset(bind, 0, sizeof(bind));

    // nombre
    std::string nombre = emp.getNombre();
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)nombre.c_str();
    bind[0].buffer_length = nombre.length();

    // cargo
    std::string cargo = emp.getCargo();
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)cargo.c_str();
    bind[1].buffer_length = cargo.length();

    // id
    int id = emp.getId();
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = (char*)&id;
    bind[2].is_unsigned = 0;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::string mensaje = "Error al vincular parámetros: " + std::string(mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        throw std::runtime_error(mensaje);
    }

    if (mysql_stmt_execute(stmt)) {
        std::string mensaje = "Error al ejecutar la sentencia: " + std::string(mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        throw std::runtime_error(mensaje);
    }

    my_ulonglong filasAfectadas = mysql_stmt_affected_rows(stmt);
    mysql_stmt_close(stmt);

    return filasAfectadas > 0;
}


std::vector<Empleado> EmpleadoDAOMySQL::selectAll() {
    std::vector<Empleado> empleados;
    const char* sql = "SELECT id, nombre, cargo FROM empleados ORDER BY id";

    if (mysql_query(this->conexion, sql)) {
        std::string mensaje = "Error en la consulta: " + std::string(mysql_error(this->conexion));
        throw std::runtime_error(mensaje);
    }

    MYSQL_RES* res = mysql_store_result(this->conexion);
    if (!res) {
        std::string mensaje = "Error al obtener resultados: " + std::string(mysql_error(this->conexion));
        throw std::runtime_error(mensaje);
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        Empleado emp;
        emp.setId(std::stoi(row[0]));
        emp.setNombre(row[1]);
        emp.setCargo(row[2]);
        empleados.push_back(emp);
    }

    mysql_free_result(res);
    return empleados;
}


EmpleadoDAOMySQL::~EmpleadoDAOMySQL() {
    if (this->conexion != nullptr) {
        mysql_close(this->conexion);
        this->conexion = nullptr;
    }
}

