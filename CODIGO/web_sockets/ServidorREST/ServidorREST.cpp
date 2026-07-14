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

        // Respuesta al cliente:
        http::response<http::string_body> response{ http::status::ok, request.version() };
        response.set(http::field::server, "REST API/1.0");
        response.set(http::field::content_type, "application/json");
        response.body() = "Respuesta del servidor " + mensaje;

        // Conexion persistente;
        response.keep_alive(request.keep_alive());

        // Analizar el target y el metodo!!

        // http://localhost:8080/items POST
        if (request.method() == http::verb::post && target == "/items") {
            response.body() = this->peticionPOST(request.body());
        }
        else {
            response.result(http::status::not_found);
            response.body() = "Ruta no encontrada";
        }

        // Calcular el tamaño de la resp: content_length
        response.prepare_payload();

        // Escribir la resp:
        http::write(socket, response);
        
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
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
