#include <iostream>
#include <boost/asio.hpp>

#include "ServidorREST.h"

int main()
{
	// Crear el contexto de E/S:
	boost::asio::io_context ioc;

	ServidorREST server(ioc, 8080);
	server.run();
}
