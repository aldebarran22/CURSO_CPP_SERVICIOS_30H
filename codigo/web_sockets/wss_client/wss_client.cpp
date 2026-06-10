// wss_client.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>
#include <thread>
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
		// Contexto de e/s
		net::io_context ioc;

		// DEfinir el contexto SSL para conexion segura:
		ssl::context ctx(ssl::context::tlsv12_client);

		// En nuestro caso, certificados autofirmados en local:
		ctx.set_verify_mode(ssl::verify_none);

		// En caso de un certificado firmado con una CA (autoridad de certificación)
		//ctx.set_verify_mode(ssl::verify_peer);
		//ctx.load_verify_file("ca.pem");

		 // Resolver intenta resolver la url de conexion al servidor:
		tcp::resolver resolver(ioc);
		websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ctx);


		// Localizar el servidor: devuelve un iterator con los endpoint del servidor
		auto const results = resolver.resolve("localhost", std::to_string(PUERTO));

		// Intentar conectar con alguno de los endpoint del servidor:
		net::connect(ws.next_layer().next_layer(), results.begin(), results.end());

		ws.next_layer().handshake(ssl::stream_base::client);
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


