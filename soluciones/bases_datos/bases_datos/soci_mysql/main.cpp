#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <iostream>
#include <optional>

#include "EmpleadoRepository.hpp"

void test1() {
    try {
        soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

        int count;
        sql << "SELECT COUNT(*) FROM empleados", soci::into(count);
        std::cout << "Numero de empleados: " << count << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al conectar con MySQL: " << e.what() << std::endl;
    }
}

std::optional<Empleado> recuperarEmpleado(int id) {
    Empleado emp;
    soci::indicator ind;

    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
    sql << "select id, nombre, cargo from empleados where id = :id", soci::use(id), soci::into(emp.id, ind),
        soci::into(emp.nombre), soci::into(emp.cargo);

    if (ind == soci::i_null) {
        return std::nullopt;
    }
    return emp;
}

void testRecuperarEmpleado() {
    auto resultado = recuperarEmpleado(1);
    if (resultado) {
        std::cout << resultado->id << " " << resultado->nombre << " " << resultado->cargo << std::endl;

    } else {
        std::cout << "Empleado no encontrado ... " << std::endl;
    }
}

void test2Repo() {
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

    EmpleadoRepository repo(sql);

    try {
        // Eliminar
        repo.eliminar(10);

        // Insertar
        repo.insertar({ 10, "Laura", "Directivo" });

        // Obtener
        int id = 10;
        auto e = repo.recuperarEmpleado(id);
        if (e) {
            std::cout << e->nombre << " - " << e->cargo << std::endl;
        }
        else {
            std::cout << "No se encuentra el empleado con id: " << id << std::endl;
        }

        // Listar
        for (const auto& emp : repo.listarTodos()) {
            std::cout << emp.id << ": " << emp.nombre << " (" << emp.cargo << ")\n";
        }

        // Actualizar
        if (e) {
            e->cargo = "Directora Creativa";
            repo.actualizar(*e);
        }

    }
    catch (std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}


int main() {
    //test1();
    test2Repo();
    //testRecuperarEmpleado();
    return 0;
}
