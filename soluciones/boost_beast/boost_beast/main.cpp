#include <iostream>
#include "HttpServer.hpp"
#include "RestApiServer.h"

#define PORT 8080

void testHttpServer() {
	try {
		boost::asio::io_context ioc;
		HttpServer servidor(ioc, PORT);
		servidor.run();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void testRestApiServer() {
	try {
		boost::asio::io_context ioc;
		RestApiServer servidor(ioc, PORT);
		servidor.run();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

int main() {
	//testHttpServer();
	testRestApiServer();

	return 0;
}
