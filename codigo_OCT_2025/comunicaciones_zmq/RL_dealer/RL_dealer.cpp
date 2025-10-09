#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
	zmq::context_t contexto(1);
	zmq::socket_t dealer(contexto, zmq::socket_type::dealer);

	// Asignar el id al cliente: 
	dealer.set(zmq::sockopt::routing_id, "cliente_1");

	dealer.connect("tcp://localhost:5555");
	std::cout << "Conectado a 5555" << std::endl;

	std::string mensaje = "soy el cliente 1";
	dealer.send(zmq::message_t(mensaje), zmq::send_flags::none);
	std::cout << "mensaje enviado " << std::endl;

	// esperar la respuesta:
	zmq::message_t respuesta;
	dealer.recv(respuesta);

	std::cout << "respuesta del servidor: " << respuesta.to_string() << std::endl;


	return 0;
}

