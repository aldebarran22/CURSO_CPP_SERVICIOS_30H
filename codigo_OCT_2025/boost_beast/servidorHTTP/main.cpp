// servidorHTTP.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "HttpServer.h"

int main()
{
    // Objeto principal del contexto:
	boost::asio::io_context ioc;
	HttpServer servidor(ioc, 8080);
	servidor.run();

	return 0;
}

