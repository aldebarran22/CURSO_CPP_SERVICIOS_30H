
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

class session : public std::enable_shared_from_this<session> {

	// Atributos de la session
	tcp::socket socket_;
	beast::flat_buffer buffer; // para almacenar y leer los datos
	http::request<http::string_body> request;
	http::response<http::string_body> response;

public:
	session(tcp::socket socket) :socket_(std::move(socket)) {}
	void start() { read_request(); }

private:
	void read_request() {
		// Utiliza una lectura asincrona

		// Coger un shared_ptr que apunta a la clase actual
		auto self = shared_from_this();

		// La lectura:
		http::async_read(socket_, buffer, request, [self](beast::error_code ec, std::size_t) {

			if (!ec) {
				// Si no hay error, manejar la peticion
				self->handler_request();
			}
			});


	}

	void handler_request() {
		// Analizar la peticion:

		std::string respuesta;

		// Recoger la peticion y el metodo HTTP:
		respuesta = "URL: " + std::string(request.target()) + " Method: " + std::string(request.method_string());

		// Montar la respuesta:
		response.version(request.version());
		response.keep_alive(request.keep_alive());
		response.result(http::status::ok);

		// Configurar las cab de HTTP:
		response.set(http::field::server, "Boost.asio");
		response.set(http::field::content_type, "text/plain");

		// Cargar la respuesta:
		response.body() = respuesta;

		// Calcular el tamaño de la respuesta:
		response.prepare_payload();

		// Escribir al cliente:
		this->write_response();

	}
	void write_response() {
		// Escribe la respuesta de forma asincrona y cerrar el socket de la conexion

		// Coger un shared_ptr que apunta a la clase actual
		auto self = shared_from_this();

		// Escribir de forma asincrona
		http::async_write(socket_, response, [self](beast::error_code ec, std::size_t) {

			// Cerrar la conexion:
			self->socket_.shutdown(tcp::socket::shutdown_send, ec);
			});

	}
};

void do_accept(tcp::acceptor& acceptor) {

	// Aceptar un cliente de forma de asincrona:
	acceptor.async_accept([&acceptor](beast::error_code ec, tcp::socket socket) {

		// Chequear si se ha producido algun error en la conexion, si no hay error:
		if (!ec) {
			// Crear e iniciar una nueva session pasando el socket:
			std::make_shared<session>(std::move(socket))->start();
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

