// ServidorREST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "ServidorREST.h"


ServidorREST::ServidorREST(net::io_context& ioc, unsigned int port):
    ioc(ioc), acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
    this->id = 1;
}


void ServidorREST::run()
{
    std::cout << "Servidor REST escuchando en el puerto: " << acceptor.local_endpoint().port() << std::endl;

    for (;;) {
        // Crear un socket:
        tcp::socket socket(ioc);

        // Aceptar peticion:
        acceptor.accept(socket);

        // Procesar la peticion:
        procesarPeticion(socket);
    }
}


void ServidorREST::procesarPeticion(tcp::socket&)
{
}

std::string ServidorREST::peticionGET()
{
    return std::string();
}

std::string ServidorREST::peticionPOST(const std::string&)
{
    return std::string();
}

std::string ServidorREST::peticionDELETE(int)
{
    return std::string();
}

ServidorREST::~ServidorREST()
{
}
