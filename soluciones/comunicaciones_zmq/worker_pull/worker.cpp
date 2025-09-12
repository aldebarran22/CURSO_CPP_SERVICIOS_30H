#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
	zmq::context_t contexto(1);
	zmq::socket_t receiver(contexto, zmq::socket_type::pull);

	std::cout << "Preparado para recibir datos ... " << std::endl;

	receiver.connect("tcp://localhost:5557");
	while (true) {
		zmq::message_t msg;

		receiver.recv(msg, zmq::recv_flags::none);
		std::cout << "Procesando: " << msg.to_string() << std::endl;
	}

	return 0;
}