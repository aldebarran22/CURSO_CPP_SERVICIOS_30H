
#include "HttpServer.hpp"
#include "RestApiServer.h"

HttpServer::HttpServer(net::io_context& ioc, unsigned short port):
	ioc_(ioc), acceptor_(ioc, tcp::endpoint(tcp::v4(), port)){}

void HttpServer::run() {
	std::cout << "Servidor HTTP escuchando en puerto: " 
		<< acceptor_.local_endpoint().port() << "..." << std::endl;

	for (;;) {
		tcp::socket socket(ioc_);
		acceptor_.accept(socket);
		handle_request(socket);
	}
}


void HttpServer::handle_request(tcp::socket& socket) {
	beast::flat_buffer buffer;

	http::request<http::string_body> req;
	http::read(socket, buffer, req);

	http::response<http::string_body> res{
		http::status::ok, req.version() };

	res.set(http::field::server, "Beast/1.0");
	res.set(http::field::content_type, "text/plain");
	res.body() = "Mensaje desde el servidor";

	http::write(socket, res);

}


