// wss_server.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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

void do_session(tcp::socket socket) {

    try {

        // Definir el websocket: sera un stream de tipo tcp:
        websocket::stream<tcp::socket> ws(std::move(socket));
        ws.accept();

        for (;;) {
            // Definir el buffer de L/E;
            beast::flat_buffer buffer;

            ws.read(buffer);
            if (!ws.binary()) {
                std::cout << "El cliente envia texto " << beast::buffers_to_string(buffer.data()) << std::endl;
                ws.text(ws.got_text());

                // Devolver al cliente el mismo mensaje:
                ws.write(buffer.data());
            }
            else {
                std::cout << "datos en binario" << std::endl;
            }
        }

    }
    catch (const beast::system_error& se) {
        if (se.code() != websocket::error::closed) {
            std::cerr << "Error en la session: " << se.what() << std::endl;

        }
        else {
            std::cout << "Cliente desconectado " << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Otro error:" << e.what() << std::endl;
    }
}

int main()
{
    // Crear el contexto de comunicacion;
    net::io_context ioc;

    // Definir el endpoint con el objeto acceptor:
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 80));

    // Capturar el numero de hilos max. soportado:
    unsigned int numHilos = std::thread::hardware_concurrency();

    // Definir el pool de hilos: 
    boost::asio::thread_pool pool(numHilos);

    while (true) {

        // Definir un socket por cada  conexion:
        tcp::socket socket(ioc);

        std::cout << "Servidor a la espera de clientes ... " << std::endl;

        // Aceptar al cliente:
        acceptor.accept(socket);

        // Lanzar un hilo para atender al cliente conectado:
        boost::asio::post(pool, [s = std::move(socket)]() mutable {
            do_session(std::move(s));
            });
    }
}
