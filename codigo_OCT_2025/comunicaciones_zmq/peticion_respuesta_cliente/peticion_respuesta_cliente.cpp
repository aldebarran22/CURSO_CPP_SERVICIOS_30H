
#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
	// El cliente se conecta al mismo puerto:
	zmq::context_t contexto(1);

	zmq::socket_t socket(contexto, zmq::socket_type::req);
	socket.connect("tcp:://localhost:5555");

	// Enviar un mensaje al servidor:
	socket.send(zmq::buffer("mensaje del cliente"), zmq::send_flags::none);

	zmq::message_t respuesta;
	socket.recv(respuesta, zmq::recv_flags::none);
	std::cout << "Respuesta del servidor: " << respuesta.to_string() << std::endl;

	return 0;
}

