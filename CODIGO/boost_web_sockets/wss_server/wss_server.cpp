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


void do_session(tcp::socket socket, ssl::context& ctx)
{
    try {
        // Definir el websocket: stream de tipo TCP:
        websocket::stream<beast::ssl_stream<tcp::socket>> ws(std::move(socket), ctx);
        ws.next_layer().handshake(ssl::stream_base::server);
        ws.accept();

        for (;;) {
            // Buffer de E/S:
            beast::flat_buffer buffer;

            ws.read(buffer);
            if (!ws.binary()) {
                std::cout << "El cliente envia texto: " << beast::buffers_to_string(buffer.data()) << std::endl;
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
            std::cerr << "Error en la sesion: " << se.what() << std::endl;
        }
        else {
            std::cout << "Cliente desconectado ... " << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Otro error : " << e.what() << std::endl;
    }
}


int main()
{
    // Definir el contexto de E/S:
    net::io_context ioc;

    // Definir el contexto SSL:
    ssl::context ctx(ssl::context::tlsv12_server);

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

