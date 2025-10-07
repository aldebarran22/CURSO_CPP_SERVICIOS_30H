#include "HttpServer.h"


HttpServer::HttpServer(net::io_context& ioc, unsigned short port):ioc_(ioc), acceptor_(ioc, tcp::endpoint(tcp::v4(), port)){}

void HttpServer::run() {
	std::cout << "Servidor HTTP " << acceptor_.local_endpoint().port() << std::endl;

	for (;;) {
		tcp::socket socket(ioc_);
		acceptor_.accept(socket);
		handle_request(socket);
	}
}

void HttpServer::handle_request(tcp::socket& socket) {
	beast::flat_buffer buffer;
	http::request<http::string_body> request;
	std::string mensaje = "";

	// Leer la peticion:
	http::read(socket, buffer, request);

	// Extraer el mensaje y la queryString con el parametro:
	std::string target = request.target();
	std::cout << "Peticion: " << target << std::endl;

	// Buscar el parametro de la url:


	// Montar la respuesta al cliente:
	http::response<http::string_body> response{ http::status::ok, request.version() };
	response.set(http::field::server, "Beast/1.0");
	response.set(http::field::content_type, "text/plain");
	response.body() = "Respuesta del servidor";

	// Escribir la respuesta:
	http::write(socket, response);
}
