
#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;

using tcp = net::ip::tcp;

#define PUERTO 8443

int main()
{
	try {
		// Crear el contexto de comunicación:
		net::io_context ioc;

		// DEfinir el contexto de seguridad:
		ssl::context ctx(ssl::context::tlsv12_client);

		// Como el certificado es autofirmado para deshabilitar la comprobación:
		ctx.set_verify_mode(ssl::verify_none);

		// En caso de que el certificado viene con una autoridad de certificación (CA):
		//ctx.set_verify_mode(ssl::verify_peer);
		//ctx.load_verify_file("ca.pem");

		tcp::resolver resolver(ioc);

		websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ctx);

		// Localizar el servidor:
		auto const results = resolver.resolve("localhost", std::to_string(PUERTO));

		// Intentar conectar con algúb endpoint del servidor:
		net::connect(ws.next_layer().next_layer(), results.begin(), results.end());

		ws.next_layer().handshake(ssl::stream_base::client);
		ws.handshake("localhost", "/");

		// Enviar y recibir informacion del servidor:
		std::string mensaje = "mensaje desde el cliente";
		ws.write(net::buffer(mensaje));

		beast::flat_buffer buffer;
		ws.read(buffer);

		std::cout << "Respuesta del servidor " << beast::make_printable(buffer.data()) << std::endl;

		ws.close(websocket::close_code::normal);
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return 0;
}

