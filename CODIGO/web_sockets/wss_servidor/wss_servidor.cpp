
#include <iostream>
#include <thread>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = boost::beast::http;
namespace ssl = net::ssl;

using tcp = net::ip::tcp;

#define PUERTO 8443


void do_session(tcp::socket socket, ssl::context& ctx) {

    try {

        // Definir el Websocket:
        websocket::stream<beast::ssl_stream<tcp::socket>> ws(std::move(socket), ctx);
        ws.next_layer().handshake(ssl::stream_base::server);
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

    // Definir el contexto SSL:
    ssl::context ctx(ssl::context::tlsv12_server);

    ctx.use_certificate_chain_file("..\\certificados\\cert.pem");
    ctx.use_private_key_file("..\\certificados\\key.pem", ssl::context::file_format::pem);

    // Definir el endpoint
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), PUERTO));

    // Capturar el número de hilos máximo:
    unsigned int numHilos = std::thread::hardware_concurrency();

    // Definir el pool de hilos:
    boost::asio::thread_pool pool(numHilos);

    std::cout << "Servidor WSS ok, con " << numHilos << " hilos" << " puerto: " << PUERTO << std::endl;

    // Esperamos clientes dentro de un bucle inf.
    while (true) {

        // Definir un socket por cada conexión:
        tcp::socket socket(ioc);

        std::cout << "Esperando clientes ..." << std::endl;

        // Aceptar el cliente que se conecta:
        acceptor.accept(socket);

        // Lanzar un hilo para atender el cliente conectado:
        boost::asio::post(pool, [s = std::move(socket), &ctx]() mutable {
            // Llamar a la tarea (función) que realiza el thread.
            do_session(std::move(s), ctx);
            });

    }


}

