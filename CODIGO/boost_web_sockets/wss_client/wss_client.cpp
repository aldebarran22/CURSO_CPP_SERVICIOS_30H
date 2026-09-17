// wss_client.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>

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

int main()
{

	try {
		// Definir el contexto de E/S:
		net::io_context ioc;

		// Definir el contexto de seguridad para el cliente:
		ssl::context ctx(ssl::context::tlsv12_client);

		// Si no tenemos una CA (Autoridad de certificacion):
		ctx.set_verify_mode(ssl::verify_none); // No verifica la CA:

		// Si tenemos una CA  (Autoridad de certificacion):
		//ctx.set_verify_mode(ssl::verify_peer);
		//ctx.load_verify_file("cap.pem");

		// Para localizar el endpoint en el servidor:
		tcp::resolver resolver(ioc);

		// Definir el websocket SSL para el cliente:
		websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ctx);


		// Localizar el servidor:
		auto const results = resolver.resolve("localhost", std::to_string(PORT);

		// Intentar conectar con el endpoint del servidor:
		net::connect(ws.next_layer().next_layer(), results.begin(), results.end());
		ws.next_layer().handshake(ssl::stream_base::client);
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


