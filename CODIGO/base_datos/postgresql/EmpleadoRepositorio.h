#pragma once

#include <libpq-fe.h>
#include <optional>
#include <vector>
#include "Empleado.h"

class EmpleadoRepository {
public:
    EmpleadoRepository(const char* cadConex);
    //std::optional<Empleado> recuperarEmpleado(int id);
    //void insertar(const Empleado& emp);
    void actualizar(const Empleado& emp);
    //void eliminar(int id);
    std::vector<Empleado> listarTodos();
    ~EmpleadoRepository();

private:
    PGconn* conn_;
};

