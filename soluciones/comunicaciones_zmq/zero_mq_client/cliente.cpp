#include <zmq.hpp>
#include <string>
#include <iostream>

void clienteZeroMQ() {
	// El cliente de zmq que se conecta con un servidor:
	zmq::context_t contexto(1);
	zmq::socket_t socket(contexto, zmq::socket_type::req);
	socket.connect("tcp://localhost:5555");

	std::string mensaje = "Mensaje del cliente";
	socket.send(zmq::buffer(mensaje), zmq::send_flags::none);

	zmq::message_t respuesta;
	socket.recv(respuesta, zmq::recv_flags::none);
	std::cout << "Respuesta del server: " << respuesta.to_string() << std::endl;
	std::cout << "Presione una tecla para continuar ..." << std::endl;
	std::cin.get();
}

int main() {
	clienteZeroMQ();
	return 0;
}