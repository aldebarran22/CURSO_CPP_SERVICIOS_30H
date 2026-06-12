// multicliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <thread>
#include <memory>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace http = beast::http;
using tcp = net::ip::tcp;

void do_accept(tcp::acceptor& acceptor) {

	// Aceptar un cliente de forma de asincrona:
	acceptor.async_accept([&acceptor](beast::error_code ec, tcp::socket socket) {

		// Chequear si se ha producido algun error en la conexion, si no hay error:
		if (!ec) {
			// Crear e iniciar una nueva session pasando el socket:
			std::make_shared<session>(std::move(socket)->start());
		}

		// Llamada recursiva para seguir recibiendo cliente:
		do_accept(acceptor);
	});
}

int main()
{

	// DEfinir el contexto de E/S:
	net::io_context ioc;

	// Inicializar el acceptor con el endpoint y el puerto:
	tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), 8080));

	do_accept(acceptor);

	std::cout << "Servidor multicliente ok, en el puerto 8080" << std::endl;

	// DEfinir un vector para lanzar varios hilos:
	
	// Multihilo:
	std::vector<std::thread> hilos;

	for (int i = 0; i < std::thread::hardware_concurrency(); i++) {

		// Creamos un hilo dentro del vector sin hacer una copia:
		hilos.emplace_back([&ioc] { ioc.run();  });
	}
	// Fin multihilo

	// Si solo queremos un solo hilo:
	// ioc.run(); // Se genera solo 1 hilo

}

