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

    // Bucle infinito del servidor para recibir a los clientes:
    for (;;) {

        // Definir un socket por cada conexion:
        tcp::socket socket(ioc);

        std::cout << "esperando clientes " << std::endl;

        // Esperar a que se conecten los clientes: accept --> acepta un cliente
        acceptor.accept(socket);

        // Lanzar un hilo con boost para atender al cliente conectado:
        // Al lanzar el hilo se le indica la tarea a realizar a través de una funcion
        boost::asio::post(pool, [s = std::move(socket)]() {
            // Es la tarea que tiene que realizar el thread, le enviamos el socket con el que se conecto
            do_session(std::move(s));
        });
    }

}

