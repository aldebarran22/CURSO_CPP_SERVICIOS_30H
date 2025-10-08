#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <thread>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {

	// Atributos de la sesion:
	tcp::socket socket_;
	beast::flat_buffer buffer_;
	http::request<http::string_body> req_;
	http::response<http::string_body> res_;

public:
	explicit session(tcp::socket socket):socket_(std::move(socket)){} // No hacemos copia del socket!

	void start() { read_request(); }

private:
	void read_request() {
		// Obtener un std::shared_ptr que apunta a la clase actual:
		auto self = shared_from_this();

		// Hacer una lectura asincrona:
		http::async_read(socket_, buffer_, req_,
			[self](beast::error_code ec, std::size_t) {
				if (!ec) self->handler_request();
			});
	}

	void handler_request() {
		// Analizar la peticion, ... operaciones ...
		std::string respuesta;

		respuesta = std::string(req_.target()) + " " + std::string(req_.method_string());
		
		// Montar la respuesta al cliente:
		// La respuesta se copia, misma version del protocolo que la peticion:
		res_.version(req_.version());
		res_.keep_alive(req_.keep_alive());
		res_.result(http::status::ok); // Codigo 200

		// Configurar las cabeceras de la respuesta:
		res_.set(http::field::server, "Boost.asio");
		res_.set(http::field::content_type, "text/plain");

		// El cuerpo de la respuesta para el cliente:
		res_.body() = respuesta;

		// Calcular automaticamente el tamaño de la respuesta:
		res_.prepare_payload();

		// Escribir la respuesta al cliente:
		write_response();

	}

	void write_response() {
		// Obtiene un std::shared_ptr que apunta a la clase actual:
		auto self = shared_from_this();

		// Cuando termina la escritura cierra la conexion:
		http::async_write(socket_, res_,
			[self](beast::error_code ec, std::size_t) {
				self->socket_.shutdown(tcp::socket::shutdown_send, ec);
			});
	}

};

void do_accept(tcp::acceptor& acceptor) {
	// Aceptar al cliente de forma asincrona:
	acceptor.async_accept([&acceptor](beast::error_code ec, tcp::socket socket) {

		// Si no hay error creamos una nueva instancia de la clase session:
		// La session se encarga de leer, procesar y escribir
		if (!ec) {

			// Se crea y se arranca:
			std::make_shared<session>(std::move(socket))->start();
		}

		// Hace una llamada recursiva para acceptar otras conexiones:
		do_accept(acceptor);
	});
}

int main()
{
	asio::io_context ioc{ 1 }; // El número de hilos que lo ejecutan

	// Crear el endpoint y el acceptor:
	tcp::endpoint endpoint(tcp::v4(), 8080);
	tcp::acceptor acceptor(ioc, endpoint);

	do_accept(acceptor);

	std::cout << "Servidor esperando en el puerto 8080" << std::endl;
	std::cout << "Num hilos: " << std::thread::hardware_concurrency();
   
	std::vector<std::thread> hilos;
	for (int i = 0; i < std::thread::hardware_concurrency(); i++) {

		// Crea el hilo dentro de la coleccion vector: no hace una copia como push_back
		hilos.emplace_back([&ioc] { ioc.run(); });
	}

	// Hacemos join de todos los hilos del vector:
	for (auto& t : hilos) {
		t.join();
	}

	// Ejecutar con un solo hilo:
	//ioc.run();
}

