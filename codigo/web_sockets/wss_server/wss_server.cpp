// wss_server.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
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

void do_session(tcp::socket socket, ssl::context& ctx) {
	try {
		// El stream tiene que ser de tipo ssl_stream y necesita el contexto de seguridad
		websocket::stream<beast::ssl_stream<tcp::socket>> ws(std::move(socket), ctx);
		ws.next_layer().handshake(ssl::stream_base::server);
		ws.accept();

		for (;;) {
			// DEfinir un buffer para leer y escribir:;
			beast::flat_buffer buffer;

			ws.read(buffer);
			ws.text(ws.got_text());

			// Devolvemos lo mismo que hemos leido
			ws.write(buffer.data());
		}

	}
	catch (const beast::system_error& se) {
		if (se.code() != websocket::error::closed) {
			std::cerr << "Error en session: " << se.what() << std::endl;
		}
		else {
			std::cout << "Cliente desconectado" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error inesperado " << e.what() << std::endl;
	}
}


int main()
{
	try {
		net::io_context ioc;

		// Definir el contexto SSL:
		ssl::context ctx(ssl::context::tlsv12_server);

		// Indicar las rutas de los certificados:
		ctx.use_certificate_chain_file("..\\certificados\\cert.pem");
		ctx.use_private_key_file("..\\certificados\\key.pem", ssl::context::file_format::pem);

		tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), PUERTO));
		std::cout << "Servidor WSS en el puerto: " << PUERTO << std::endl;

		for (;;) {
			// Crear el socket para conectar con un cliente
			tcp::socket socket(ioc);

			// Aceptar un cliente:
			acceptor.accept(socket);

			// Lanzar un hilo para atender al cliente conectado:
			std::thread{ do_session, std::move(socket), std::ref(ctx) }.detach(); // Desconectado del hilo principal: main

		}
	

	} catch (const std::exception& e){
		std::cerr << "error: " << e.what() << std::endl;
	}
}

