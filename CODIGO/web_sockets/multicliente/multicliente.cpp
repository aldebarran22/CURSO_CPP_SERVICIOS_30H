// multicliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <vector>
#include <memory>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

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
    session(tcp::socket socket): socket_(std::move(socket)){}
    void start() { read_request();  }

private:
    void read_request(){
        // Utilizamos lectura asincrona:

        // Coger un shared_ptr que apunta a la clase actual:
        auto self = shared_from_this();

        // Leer la peticion:
        http::async_read(socket_, buffer, request, [self](beast::error_code ec, std::size_t) {

            if (!ec) {
                // Si no hay error, se analiza la peticion:
                self->handler_request();
            }
        })
    }


    void handler_request(){}


    void write_response(){}
};

void do_accept(tcp::acceptor& acceptor) {
    
    // Aceptar un cliente de forma asincrona:
    acceptor.async_accept([&acceptor](beast::error_code ec, tcp::socket socket) {

        // Comprobar si se han producido errores en la conexion:
        if (!ec) {
            // Crear e iniciar una nueva session:
            std::make_shared<session>(std::move(socket))->start();
        }

        // Llamada recursiva para seguir recibiendo clientes:
        do_accept(acceptor);
    });
}

int main()
{
    // Crear el contexto de comunicacion;
    net::io_context ioc;

    // Definir el endpoint con el objeto acceptor:
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

    do_accept(acceptor);

    // Con varios hilos:
    std::vector<std::thread> hilos;
    unsigned int numhilos = std::thread::hardware_concurrency();

    for (int i = 0; i < numhilos; i++) {
        // Lanzar un contexto io por cada uno de los hilos
        hilos.emplace_back([&ioc] { ioc.run();  });
    }

    // Un unico hilo:
    //ioc.run();
}

