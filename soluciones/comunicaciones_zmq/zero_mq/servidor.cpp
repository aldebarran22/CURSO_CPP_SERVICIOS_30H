#include <iostream>
#include <zmq.hpp>

void servidorZeroMQ() {
	// Poner en marcha un servidor de ZeroMQ
	zmq::context_t context(1);
	zmq::socket_t socket(context, zmq::socket_type::rep);
	socket.bind("tcp://*:5555");

	std::cout << "Servidor escuchando en el puerto tcp: 5555" << std::endl;

	while (true) {
		zmq::message_t request;
		socket.recv(request, zmq::recv_flags::none);
		std::cout << "Recibido: " << request.to_string() << std::endl;

		std::string reply = "Mensaje del servidor!";
		socket.send(zmq::buffer(reply), zmq::send_flags::none);
	}

}

int main() {
	servidorZeroMQ();
	return 0;
}
