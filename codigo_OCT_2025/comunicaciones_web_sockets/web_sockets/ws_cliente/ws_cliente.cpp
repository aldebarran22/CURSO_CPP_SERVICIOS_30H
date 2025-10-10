
#include <iostream>
#include <thread>
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
		net::io_context ioc;
		tcp::resolver resolver(ioc);
		websocket::stream<tcp::socket> ws(ioc);

		// Localizar el servidor:
		auto const results = resolver.resolve("localhost", "80");

		// Intenta conectar con alguno de los endpoints del servidor:
		net::connect(ws.next_layer(), results.begin(), results.end());

		ws.handshake("localhost", "/");

		// Enviar y recibir informacion:
		std::string mensaje = "mensaje desde el cliente";
		ws.write(net::buffer(mensaje));

		beast::flat_buffer buffer;
		ws.read(buffer);
		std::cout << "Respuesta del servidor " << beast::make_printable(buffer.data()) << std::endl;

		// Cerrar la conexion:
		ws.close(websocket::close_code::normal);

	}
	catch (const std::exception& e) {
		std::cerr << "Error en el cliente: " << e.what() << std::endl;
	}
	return 0;
}

