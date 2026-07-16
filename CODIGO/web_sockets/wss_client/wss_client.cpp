// wss_client.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>

#define PUERTO 443

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = boost::beast::http;
namespace ssl = net::ssl;

using tcp = net::ip::tcp;


int main()
{
	try {
		// Crear el contexto de comunicaciones
		net::io_context ioc;

		// Definir el contexto de seguridad en el cliente:
		ssl::context ctx(ssl::context::tlsv12_client);

		// Si el certificado es autofirmado sin una CA (Autoridad de certificacion)
		// Deshabilita la comprobación
		ctx.set_verify_mode(ssl::verify_none);

		// Si el certificado viene de una CA (Autoridad de certificacion)
		//ctx.set_verify_mode(ssl::verify_peer);
		//ctx.load_verify_file("cap.pem");


		// Para localizar un endpoint en el servidor:
		tcp::resolver resolver(ioc);

		// Definir el websocket para ssl:
		websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ctx);

		// Localizar el servidor:
		auto const results = resolver.resolve("localhost", std::to_string(PUERTO));

		// Intentar conectar con algún endpoint del servidor;
		net::connect(ws.next_layer().next_layer(), results.begin(), results.end());

		ws.next_layer().handshake(ssl::stream_base::client);
		ws.handshake("localhost", "/");

		// Enviar y recibir informacion del servidor:
		std::string mensaje = "mensaje desde el cliente";
		ws.write(net::buffer(mensaje));

		beast::flat_buffer buffer;
		ws.read(buffer);

		std::cout << "Respuesta del Servidor " << beast::make_printable(buffer.data()) << std::endl;

		ws.close(websocket::close_code::normal);

	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

