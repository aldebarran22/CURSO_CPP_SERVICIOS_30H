// postgresql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <libpq-fe.h>

#include "Empleado.h"
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


void testListado() {
    // DEfinir la cadena de conexion:
    const char* cadConex = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";
    PGconn* conn = PQconnectdb(cadConex);


    if (PQstatus(conn) != CONNECTION_OK) {
        std::cerr << "Error en la conexion " << PQerrorMessage(conn) << std::endl;
        PQfinish(conn);
        return 1;
    }
    else {
        std::cout << "conexion ok!" << std::endl;
    }

    // Ejecutar una consultar:
    PGresult* res = PQexec(conn, "select id, nombre, cargo from tbempleados");

    if (PQresultStatus(res) == PGRES_TUPLES_OK) {

        int rows = PQntuples(res);
        std::cout << "Listado de " << rows << " filas: " << std::endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << PQgetvalue(res, i, j) << " ";
            }
            std::cout << std::endl;
        }
        PQclear(res);
    }
    else {
        std::cout << PQerrorMessage(conn) << std::endl;
    }

    PQfinish(conn);
}

int main()
{
    testPostgresRepo();
	return 0;
}
