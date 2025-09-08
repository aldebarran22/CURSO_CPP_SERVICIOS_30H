#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>

#include "cliente_web_socket.hpp"

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace asio = boost::asio;

using tcp = asio::ip::tcp;

void clienteWebSocket() {

	try {
		// Definir el contexto de in-out
		asio::io_context ioc;

		// Resolver DNS:
		tcp::resolver resolver(ioc);
		auto const results = resolver.resolve("echo.websocket.events", "80");

		// Crear el WebSocket:
		websocket::stream<tcp::socket> ws(ioc);

		// Conectar al Servidor:
		asio::connect(ws.next_layer(), results.begin(), results.end());

		// Handshake WebSocket:
		ws.handshake("echo.websocket.events", "/");

		// Enviar el mensaje:
		std::string msg = "Mensaje de Boost.Beast";
		ws.write(asio::buffer(msg));

		// Leer la respuesta:
		beast::flat_buffer buffer;
		ws.read(buffer);
		std::cout << "Respuesta del Servidor: " << beast::make_printable(buffer.data()) << std::endl;

		// Leer una segunda respuesta:
		beast::flat_buffer buffer2;
		ws.read(buffer2);
		std::cout << "Respuesta 2 del Servidor: " << beast::make_printable(buffer2.data()) << std::endl;

		// Inspeccionar todos los endpoint:
		for (auto const& entry : results) {
			auto endpoint = entry.endpoint();
			std::cout << "IP: " << endpoint.address().to_string()
				<< ", Puerto: " << endpoint.port()
				<< ", Protocolo: " << (endpoint.protocol() == tcp::v4() ? "IPv4" : "IPv6")
				<< std::endl;
		}


		// Cerrar la conexion:
		ws.close(websocket::close_code::normal);

	} catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
	
}