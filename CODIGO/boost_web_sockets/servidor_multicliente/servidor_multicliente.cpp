// servidor_multicliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <vector>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = boost::beast::http;

using tcp = net::ip::tcp;

class session : public std::enable_shared_from_this<session> {

    // Atributos de la session:
    tcp::socket socket_;
    beast::flat_buffer buffer; // para almacenar y leer datos

    // Objetos request / response (leer / escribir del cliente)
    http::request<http::string_body> request;
    http::response<http::string_body> response;

public:
    session(tcp::socket socket) : socket_(std::move(socket)) {}
    void start() { read_request(); }

private:
    void read_request() {
        // Utilizamos lectura asincrona:

        // Coger un shared_ptr que apunta a la clase actual:
        auto self = shared_from_this();

        // Leer la peticion:
        http::async_read(socket_, buffer, request, [self](beast::error_code ec, std::size_t) {

            if (!ec) {
                // Si no hay error, se analiza la peticion:
                self->handler_request();
            }
            });
    }


    void handler_request() {
        // Analizar la peticion del cliente:
        std::string respuesta;

        // Url de la peticion y el metodo HTTP:
        respuesta = "URL: " + std::string(request.target()) + " Method: " + std::string(request.method_string());

        // Montar la respuesta:
        response.version(request.version());
        response.keep_alive(request.keep_alive());
        response.result(http::status::ok);

        // Configurar las cabeceras de la respuesta:
        response.set(http::field::server, "Boost.asio");
        response.set(http::field::content_type, "text/plain");

        // Cargar la respuesta;
        response.body() = respuesta;

        // Calcular el tamaños de la respuesta:
        response.prepare_payload();

        // Escribir en el cliente;
        this->write_response();
    }


    void write_response() {
        // Escribir la respuesta al cliente de forma asincrona y cerrar el socket de la conexion:

        // Coger un shared_ptr que apunta a la clase actual:
        auto self = shared_from_this();

        // Escribir de forma asincrona
        http::async_write(socket_, response, [self](beast::error_code ec, size_t) {

            // Cerrar la conexion (del socket)
            self->socket_.shutdown(tcp::socket::shutdown_send, ec);
            });
    }
};


void do_accept(tcp::acceptor& acceptor) {
    std::cout << "Aceptando clientes." << std::endl;

    acceptor.async_accept([&acceptor](beast::error_code ec, tcp::socket socket) {

        if (!ec) {
            // Crear e iniciar una nueva sesion para atender al cliente que ha conectado:
            std::cout << "Se crea una nueva sesion " << std::endl;
            std::make_shared<session>(std::move(socket))->start();
        }

        // Llamada recursiva para continuar aceptando clientes
        do_accept(acceptor);
    });
}

int main()
{
    // Definir el contexto de E/S:
    net::io_context ioc;

    // Definir el endpoint en el server:
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

    do_accept(acceptor);

    // Numero maximo de hilos del procesador:
    unsigned int numHilos = std::thread::hardware_concurrency();

    // El vector de hilos:
    std::vector<std::thread> hilos;

    for (int i = 0; i < numHilos; i++) {
        // Lanzar un contexto de E/S por cada hilo:
        hilos.emplace_back([&ioc] { ioc.run(); });
    }

    for (auto& h : hilos) {
        h.join();
    }

}

