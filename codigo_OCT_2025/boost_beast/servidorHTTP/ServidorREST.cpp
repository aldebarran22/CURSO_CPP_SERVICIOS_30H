#include "ServidorREST.h"


ServidorREST::ServidorREST(net::io_context& ioc, unsigned short port) :ioc_(ioc), acceptor_(ioc, tcp::endpoint(tcp::v4(), port)) {}


void ServidorREST::run() {
	std::cout << "Servidor REST " << acceptor_.local_endpoint().port() << std::endl;

	for (;;) {
		tcp::socket socket(ioc_);
		acceptor_.accept(socket);
		handle_request(socket);
	}
}

void ServidorREST::handle_request(tcp::socket& socket) {

}

