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

void ServidorREST::procesarPeticion(tcp::socket&)
{
}


ServidorREST::~ServidorREST()
{
}
