// wss_server.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>

#define PORT 443

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = boost::beast::http;
namespace ssl = net::ssl;

using tcp = net::ip::tcp;

int main()
{
    // Definir el contexto de E/S:
    net::io_context ioc;

    // Definir el contexto SSL:
    ssl::context ctx(ssl::context::tslv12_server);

    // Indicar cuales son los ficheros de los certificados:
    ctx.use_certificate_chain_file("..\\certificados\\cert.pem");
    ctx.use_private_key_file("..\\certificados\\key.pem", ssl::context::file_format::pem);

    // Definir el endpoint en el server:
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), PORT));

    // Numero maximo de hilos del procesador:
    unsigned int numHilos = std::thread::hardware_concurrency();

    // Construir el pool de hilos:
    boost::asio::thread_pool pool(numHilos);

    while (true) {
        // Es un socket por cada conexion:
        tcp::socket socket(ioc);

        std::cout << "Servidor a la espera de clientes ..." << std::endl;

        // Aceptar un nuevo cliente:
        acceptor.accept(socket);

        // Lanzar el hilo para atender al cliente que acaba de conectar:
        boost::asio::post(pool, [s = std::move(socket), &ctx]() mutable {
            do_session(std::move(s), ctx);
        });
    }
}

