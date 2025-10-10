// ws_servidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void do_sesion(tcp::socket socket) {

	try {
		websocket::stream<tcp::socket> ws(std::move(socket));
		ws.accept();

		for (;;) {
			beast::flat_buffer buffer;
			ws.read(buffer);
			ws.text(ws.got_text());
			ws.write(buffer.data()); // Hace un echo de la cadena recibida.
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
	net::io_context ioc;
	tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 80));

	try {

		std::cout << "Servidor ok en el puerto 80 " << std::endl;

		for (;;) {
			// Definir un socket (1 por cada cliente)
			tcp::socket socket(ioc);

			std::cout << "Esperando clientes ...";
			acceptor.accept(socket);

			// Creamos un hilo para atender a cada cliente:
			std::thread{ do_sesion, std::move(socket) }.detach(); // se desconecta del hilo main
		}

	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
   
}


