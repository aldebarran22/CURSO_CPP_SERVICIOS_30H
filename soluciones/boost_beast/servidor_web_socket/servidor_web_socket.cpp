#include "servidor_web_socket.hpp"

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

void servidorWebSocket() {
    try {
        asio::io_context ioc;

        // Crear socket de escucha
        tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));
        std::cout << "Servidor WebSocket escuchando en puerto 8080..." << std::endl;

        for (;;) {
            // Aceptar conexión
            tcp::socket socket(ioc);
            acceptor.accept(socket);

            // Crear stream WebSocket
            websocket::stream<tcp::socket> ws(std::move(socket));

            // Realizar handshake
            ws.accept();

            // Bucle de eco
            for (;;) {
                beast::flat_buffer buffer;
                ws.read(buffer);

                std::string msg = beast::buffers_to_string(buffer.data());
                std::cout << "Mensaje recibido: " << msg << std::endl;

                // Enviar eco
                ws.write(asio::buffer(msg));
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}