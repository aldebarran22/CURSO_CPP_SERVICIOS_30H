// ws_server.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>

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
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 80));

    // Numero maximo de hilos del procesador:
    unsigned int numHilos = std::thread::harware_concurrency();

    // Construir el pool de hilos:
    boost::asio::thread_pool pool(numHilos);


}

