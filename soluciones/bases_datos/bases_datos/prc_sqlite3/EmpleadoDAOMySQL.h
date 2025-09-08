#pragma once
#include <mysql/mysql.h>       // General MySQL API
#include <mysql/mysql_version.h> // Opcional para verificar versi�n

#include "IEmpleadoDAO.h"
#include "Empleado.h"

class EmpleadoDAOMySQL : public IEmpleadoDAO {

private:
	MYSQL* conexion;

public:

	EmpleadoDAOMySQL(const char* path);

	// Heredado v�a IEmpleadoDAO
	bool create(Empleado*) override;
	Empleado read(int) override;
	bool del(int) override;
	bool update(Empleado) override;
	std::vector<Empleado> selectAll() override;

	~EmpleadoDAOMySQL();
};


