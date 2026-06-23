// ServidorREST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <boost/asio.hpp>

#include "ServidorREST.h"

namespace net = boost::asio;


int main()
{
    // Crear el contexto de comunicación:
    net::io_context ioc;

    ServidorREST server(ioc, 8080);
    server.run();
}
