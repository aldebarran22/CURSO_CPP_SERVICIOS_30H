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

        else if (request.method() == http::verb::get && target == "/items") {
            response.body() = this->peticionGET();

        }
        else if (request.method() == http::verb::delete_ && request.target().starts_with("/items/")) {
            std::string id_str = target.substr(std::string("/items/").size());

            try {
                int id = std::stoi(id_str);
                response.body() = this->peticionDELETE(id);
            }
            catch (...) {
                response.result(http::status::bad_request);
                json resp = { {"error", "Falta id a borrar"} };
                response.body() = resp.dump();
            }
        }

        else {
            response.result(http::status::not_found);
            json resp = { {"error", "url no mapeada o verbo no implementado"} };
            response.body() = resp.dump();
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
    json resp;

    for (const auto& [id, value] : this->items) {
        json aux = { {"id", id}, {"value", value} };
        resp.push_back(aux);
    }

    return resp.dump();
}

std::string ServidorREST::peticionPOST(const std::string& body)
{
    json req = json::parse(body);

    // Validacion del json recibido:
    if (!req.contains("value") || !req["value"].is_string()) {
        json resp = {
            {"error", "Campo value obligatorio y debe ser un string"}
        };

        return resp.dump();
    }

    // Recuperar el value y cargarlo en la colección con la clave id generada:
    std::string value = req["value"];
    int id = this->id++;

    // Lo almacenamos en el mapa:
    this->items[id] = value;
    json resp = { {"id", id}, {"value", value} };

    return resp.dump();
}

std::string ServidorREST::peticionDELETE(int id)
{
    // Comprobar si existe el id en el mapa: con un iterator
    if (this->items.find(id) != this->items.end()) {
        this->items.erase(id);

        json resp = { {"id", id}, { "mensaje", "Item eliminado"} };
        return resp.dump();
    }
    else {
        // No existe el elemento:
        json resp = { {"id", id}, { "mensaje", "No existe el item"} };
        return resp.dump();
    }
}

ServidorREST::~ServidorREST()
{
}
