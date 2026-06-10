#pragma once
#include <libpq-fe.h>
#include <optional>
#include <vector>
#include "Empleado.hpp"

class EmpleadoRepository {
public:
    EmpleadoRepository(PGconn* conn);
    std::optional<Empleado> recuperarEmpleado(int id);
    void insertar(const Empleado& emp);
    void actualizar(const Empleado& emp);
    void eliminar(int id);
    std::vector<Empleado> listarTodos();

private:
    PGconn* conn_;
};

