#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
	zmq::context_t contexto(1);
	zmq::socket_t sender(contexto, zmq::socket_type::push);

	std::cout << "Preparado para enviar tareas ... " << std::endl;

	sender.bind("tcp://*:5557");
	for (int i = 0; i < 10; i++) {
		sender.send(zmq::buffer("Tarea: " + std::to_string(i + 1)), zmq::send_flags::none);
	}

	return 0;
}
