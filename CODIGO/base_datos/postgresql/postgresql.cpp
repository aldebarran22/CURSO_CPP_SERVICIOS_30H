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
		}
	}
	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int main()
{
	testConexion();
}

