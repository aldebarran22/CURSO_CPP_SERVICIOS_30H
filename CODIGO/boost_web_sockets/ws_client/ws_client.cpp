// ws_client.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = boost::beast::http;

using tcp = net::ip::tcp;

int main()
{

	try {
		// Definir el contexto de E/S:
		net::io_context ioc;

		// Para localizar el endpoint en el servidor:
		tcp::resolver resolver(ioc);

		// Definir el websocket para el cliente:
		websocket::stream<tcp::socket> ws(ioc);

		// Localizar el servidor:
		auto const results = resolver.resolve("localhost", "80");

		// Intentar conectar con el endpoint del servidor:
		net::connect(ws.next_layer(), results.begin(), results.end());

		ws.handshake("localhost", "/");

		// Enviar y recibir informacion con el servidor:
		std::string mensaje = "mensaje desde el cliente";
		ws.write(net::buffer(mensaje));

		beast::flat_buffer buffer;
		ws.read(buffer);

		std::cout << "Respuesta del servidor " << beast::make_printable(buffer.data()) << std::endl;

		// Desconectar el ws de una forma normal:
		ws.close(websocket::close_code::normal);

	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}

