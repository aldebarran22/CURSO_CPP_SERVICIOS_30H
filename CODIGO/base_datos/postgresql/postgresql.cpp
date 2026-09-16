// postgresql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <libpq-fe.h>
#include <iostream>

void testConexion() {
	try {
		const char* conninfo = "host=127.0.0.1 port=5433 dbname=empresa3 user=antonio password=antonio";
		PGconn* conn = PQconnectdb(conninfo);

		if (PQstatus(conn) == CONNECTION_BAD) {			
			std::cout << "Falla conexion" << std::endl;
		}
		else {
			std::cout << "Conexion ok" << std::endl;

			// Listar los empleados:
			PGresult* res = PQexec(conn, "select id, nombre, cargo from empleados");

			if (PQresultStatus(res) != PGRES_TUPLES_OK) {
				std::string mensaje = PQresultErrorMessage(res);								
			}
			else {
				// Imprimir los resultados:
				int n = PQntuples(res);
				for (int i = 0; i < n; i++) {
					std::cout <<
						PQgetvalue(res, i, 0) <<
						PQgetvalue(res, i, 1) <<
						PQgetvalue(res, i, 2) << std::endl;
				}

			}

			PQclear(res);

		}

		// Liberar la conexion:
		PQfinish(conn);
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int main()
{
	testConexion();
}

