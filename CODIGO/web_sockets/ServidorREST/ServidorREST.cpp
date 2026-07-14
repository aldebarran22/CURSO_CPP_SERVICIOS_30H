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
        std::cout << "cliente conectado" << std::endl;

        // Procesar la peticion:
        procesarPeticion(socket);
    }
}


void ServidorREST::procesarPeticion(tcp::socket& socket)
{
    beast::flat_buffer buffer;
    http::request<http::string_body> request;
    std::string mensaje = "";
    std::string metodo;
    std::string target;

    try {
        // Leer la peticion:
        http::read(socket, buffer, request);

        // Extraer la url y el metodo:
        target = request.target();
        metodo = request.method_string();

        std::cout << "Peticion: " << target << " metodo: " << metodo << std::endl;

    }
    catch (const std::exception& e) {

    }
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
