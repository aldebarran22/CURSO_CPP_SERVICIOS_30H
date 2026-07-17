// multicliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <vector>

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

