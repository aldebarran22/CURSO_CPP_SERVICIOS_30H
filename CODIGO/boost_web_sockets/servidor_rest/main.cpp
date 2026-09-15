// servidor_rest.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <boost/asio.hpp>
#include "ServidorREST2.h"

int main()
{
	// Crear el contexto E/S:
	boost::asio::io_context ioc;

	ServidorREST server(ioc, 8080);
	server.run();
}

