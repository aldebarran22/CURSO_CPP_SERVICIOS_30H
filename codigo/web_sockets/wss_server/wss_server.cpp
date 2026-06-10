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


int main()
{
	net::io_context ioc;

	// Definir el contexto SSL:
	ssl::context ctx(ssl::context::tlsv12_server);

	// Indicar las rutas de los certificados:
	ctx.use_certificate_chain_file("cert.pem");
	ctx.use_private_key_file("key.pem", ssl::context::file_format::pem);

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
	}
}

