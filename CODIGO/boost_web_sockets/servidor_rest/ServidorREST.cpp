#include "ServidorREST.h"

ServidorREST::ServidorREST(net::io_context& ioc, unsigned int port):ioc(ioc),
acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
	this->id = 1;
}

void ServidorREST::run()
{
	std::cout << "Servidor REST escuchando en el puerto " << acceptor.local_endpoint().port()
		<< std::endl;

	while(true) {
		// Crear socket para recibir clientes:
		tcp::socket socket(ioc);

		// Aceptar peticiones:
		acceptor.accept(socket);
		std::cout << "Cliente conectado ..." << std::endl;

		// Procesar la peticion:
		procesarPeticion(socket);
	}
}

void ServidorREST::procesarPeticion(tcp::socket& socket)
{
	beast::flat_buffer buffer;
	http::request<http::string_body> request;
	std::string metodo;
	std::string target;

	try {
		// Leer la peticion del cliente:
		http::read(socket, buffer, request);

		// Extraer la URL y el metodo:
		target = request.target();
		metodo = request.method_string();

		std::cout << "Target: " << target << " Metodo: " << metodo << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << "error: " << e.what() << std::endl;
	}
}


ServidorREST::~ServidorREST()
{
}
