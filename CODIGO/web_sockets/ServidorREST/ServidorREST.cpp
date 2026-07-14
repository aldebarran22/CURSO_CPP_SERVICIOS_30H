// ServidorREST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "ServidorREST.h"

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

ServidorREST::ServidorREST(net::io_context& ioc, unsigned int port)
{
}

ServidorREST::~ServidorREST()
{
}
