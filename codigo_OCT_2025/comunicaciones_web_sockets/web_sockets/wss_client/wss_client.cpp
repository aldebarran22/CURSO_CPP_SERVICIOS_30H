
#include <iostream>
#include <thread>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

#define PORT 8443

int main()
{
	try {
		net::io_context ioc;
		ssl::context ctx(ssl::context::tlsv12_client);

		// Para pruebas locales:
		ctx.set_verify_mode(ssl::verify_none);

		tcp::resolver resolver(ioc);
		websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ctx);

		// Localizar el servidor:
		auto const results = resolver.resolve("localhost", std::to_string(PORT));

		// Intenta conectar con alguno de los endpoints del servidor:
		net::connect(ws.next_layer().next_layer(), results.begin(), results.end());

		// Hacer el handshake:
		ws.next_layer().handshake(ssl::stream_base::client);
		ws.handshake("localhost", "/");

		std::string mensaje = "mensaje desde el cliente WSS";
		ws.write(net::buffer(mensaje));

		beast::flat_buffer buffer;
		ws.read(buffer);
		std::cout << "Respuesta del servidor WSS " << beast::make_printable(buffer.data()) << std::endl;

		// Cerrar la conexion:
		ws.close(websocket::close_code::normal);

	}
	catch (const std::exception& e) {
		std::cerr << "Error en el cliente WSS " << e.what() << std::endl;
	}
	return 0;
}
