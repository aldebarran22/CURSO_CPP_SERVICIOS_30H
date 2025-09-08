// servidorWSS.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

void run_server_1_mensaje(net::io_context& ioc, ssl::context& ctx, unsigned short port) {
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

    std::cout << "Servidor WSS escuchando en el puerto: " << port << std::endl;
    std::cout << "conectar con websocat.exe wss://localhost:" << port << std::endl;

    for (;;) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);

        ssl::stream<tcp::socket> ssl_stream(std::move(socket), ctx);
        ssl_stream.handshake(ssl::stream_base::server);

        websocket::stream<ssl::stream<tcp::socket>> ws(std::move(ssl_stream));
        ws.accept();

        beast::flat_buffer buffer;
        ws.read(buffer);
        ws.text(ws.got_text());
        std::cout << "Mensaje recibido: " << beast::make_printable(buffer.data()) << std::endl;

        ws.write(buffer.data());
    }
}

void run_server_n_mensajes(net::io_context& ioc, ssl::context& ctx, unsigned short port) {
    tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), port));

    std::cout << "Servidor WSS escuchando en el puerto: " << port << std::endl;
    std::cout << "conectar con websocat --insecure wss://localhost:" << port << std::endl;

    for (;;) {
        tcp::socket socket(ioc);
        acceptor.accept(socket);

        ssl::stream<tcp::socket> ssl_stream(std::move(socket), ctx);
        ssl_stream.handshake(ssl::stream_base::server);

        websocket::stream<ssl::stream<tcp::socket>> ws(std::move(ssl_stream));
        ws.accept();

        beast::flat_buffer buffer;
        // Bucle interno para mantener la sesión activa
        for (;;) {
            buffer.clear(); // Limpia el buffer antes de cada lectura

            boost::system::error_code ec;
            ws.read(buffer, ec);

            if (ec == websocket::error::closed) {
                std::cout << "Cliente desconectado" << std::endl;
                break;
            }
            else if (ec) {
                std::cerr << "Error de lectura: " << ec.message() << std::endl;
                break;
            }

            ws.text(ws.got_text());
            std::cout << "Mensaje recibido: " << beast::make_printable(buffer.data()) << std::endl;

            ws.write(buffer.data(), ec);
            if (ec) {
                std::cerr << "Error de escritura: " << ec.message() << std::endl;
                break;
            }
        }
    }
}


int main()
{
    try {
        boost::asio::io_context ioc;
        boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv12);

        ctx.set_options(
            boost::asio::ssl::context::default_workarounds |
            boost::asio::ssl::context::no_sslv2 |
            boost::asio::ssl::context::no_sslv3 |
            boost::asio::ssl::context::single_dh_use
        );

        ctx.use_certificate_file("cert.pem", boost::asio::ssl::context::pem);
        ctx.use_private_key_file("key.pem", boost::asio::ssl::context::pem);


        //run_server_1_mensajes(ioc, ctx, 9002);
        run_server_n_mensajes(ioc, ctx, 9002);


        // websocat --insecure wss://localhost:9002

    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
