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
using tcp = net::ip::tcp;

int main()
{
    // Crear el contexto de comunicacion:
    net::io_context ioc;

    // Definir el endpoint: 
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 80));

    // Definir un pool de hilos y el numero total se obtiene del HW:
    unsigned int num_hilos = std::thread::hardware_concurrency();

    // Inicializar el pool de hilos:
    boost::asio::thread_pool pool(num_hilos);

    std::cout << "Servidor ok, con " << num_hilos << " hilos" << std::endl;



}

