// ws_servidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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
      
        // Definir el Websocket:
        websocket::stream<tcp::socket> ws(std::move(socket));       
        ws.accept();

        for (;;) {
            // Definir el buffer de L/E:
            beast::flat_buffer buffer;
                       
            ws.read(buffer);
            ws.text(ws.got_text());
            
            // Devolver al cliente el mismo mensaje:
            ws.write(buffer.data());
        }
    
    }
    catch (const beast::system_error& se) {
        if (se.code() != websocket::error::closed) {
            std::cerr << "Error en la sesion: " << se.what() << std::endl;
        }
        else {
            std::cout << "Cliente desconectado" << std::endl;

        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error inesperado: " << e.what() << std::endl;
    }

}

int main()
{
    // Crear el contexto de comunicación:
    net::io_context ioc;

    // Definir el endpoint
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 80));

    // Capturar el número de hilos máximo:
    unsigned int numHilos = std::thread::hardware_concurrency();

    // Definir el pool de hilos:
    boost::asio::thread_pool pool(numHilos);

    std::cout << "Servidor ok, con " << numHilos << " hilos" << std::endl;

    // Esperamos clientes dentro de un bucle inf.
    while (true) {

        // Definir un socket por cada conexión:
        tcp::socket socket(ioc);

        std::cout << "Esperando clientes ..." << std::endl;

        // Aceptar el cliente que se conecta:
        acceptor.accept(socket);

        // Lanzar un hilo para atender el cliente conectado:
        boost::asio::post(pool, [s = std::move(socket)]() mutable {
            // Llamar a la tarea (función) que realiza el thread.
            do_session(std::move(s));
        });

    }


}

