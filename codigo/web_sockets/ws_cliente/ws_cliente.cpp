// ws_cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

int main()
{
    try {
        // Definir el contexto:
        net::io_context ioc;

        // Resolver intenta resolver la url de conexion al servidor:
        tcp::resolver resolver(ioc);
        websocket::stream<tcp::socket> ws(ioc);

        // Localizar el servidor: devuelve un iterator con los endpoint del servidor
        auto const results = resolver.resolve("localhost", "80");

        // Intentar conectar con alguno de los endpoint del servidor:
        net::connect(ws.next_layer(), results.begin(), results.end());

        ws.handshake("localhost", "/");

        // Enviar y recibir informacion del servidor:
        std::string mensaje = "mensaje desde el cliente";
        ws.write(net::buffer(mensaje));

        beast::flat_buffer buffer;
        ws.read(buffer);

        std::cout << "Respuesta del servidor " << beast::make_printable(buffer.data()) << std::endl;

        // Cerrar la conexion:
        ws.close(websocket::close_code::normal);
    }
    catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
    }
    return 0;
}