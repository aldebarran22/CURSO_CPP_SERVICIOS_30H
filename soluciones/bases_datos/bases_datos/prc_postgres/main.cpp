#include <iostream>
#include <libpq-fe.h>

int testConexion() {
    const char* conninfo = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";

    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Error de conexión: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }

    std::cout << "Conexion exitosa a PostgreSQL" << std::endl;

    PQfinish(conn);
}

#include <iostream>
#include <libpq-fe.h>
#include "EmpleadoRepository.hpp"

void testPostgresRepo() {
    const char* conninfo = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";
    PGconn* conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Error de conexion: " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return;
    }

    EmpleadoRepository repo(conn);

    try {
        // Eliminar
        //repo.eliminar(10);

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
    catch (const std::exception& ex) {
        std::cerr << "ERROR: " << ex.what() << std::endl;
    }

    PQfinish(conn);
}


int main() {
    //testConexion();
    testPostgresRepo();
    return 0;
}
