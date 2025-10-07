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

}
