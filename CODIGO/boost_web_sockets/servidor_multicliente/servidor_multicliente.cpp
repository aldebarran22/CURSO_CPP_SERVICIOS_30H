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

int main()
{
    // Definir el contexto de E/S:
    net::io_context ioc;

    // Definir el endpoint en el server:
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

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

