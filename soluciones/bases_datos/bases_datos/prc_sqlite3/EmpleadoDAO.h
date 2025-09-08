#pragma once

#include <sqlite3.h>
#include "IEmpleadoDAO.h"
#include "Empleado.h"

class EmpleadoDAO : public IEmpleadoDAO {

private:
	sqlite3* conexion;

public:

	EmpleadoDAO(const char *path);

	// Heredado vía IEmpleadoDAO
	bool create(Empleado *) override;
	Empleado read(int) override;
	bool del(int) override;
	bool update(Empleado) override;
	std::vector<Empleado> selectAll() override;

	~EmpleadoDAO();
};

