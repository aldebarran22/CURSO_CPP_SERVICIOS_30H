// postgresql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <libpq-fe.h>


int main()
{
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
	PGresult* res = PQexec(conn, "select id, nombre, cargo from empleados");

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

	PQfinish(conn);
	return 0;
}
