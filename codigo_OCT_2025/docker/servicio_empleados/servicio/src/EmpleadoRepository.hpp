#pragma once
#include <soci/soci.h>
#include <optional>
#include <vector>
#include "Empleado.hpp"


class EmpleadoRepository {
public:
    EmpleadoRepository(soci::session& sql);
    std::optional<Empleado> recuperarEmpleado(int id);
    void insertar(const Empleado& emp);
    void actualizar(const Empleado& emp);
    void eliminar(int id);
    std::vector<Empleado> listarTodos();


private:
    soci::session& sql_;
};

