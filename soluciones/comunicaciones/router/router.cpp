#include <zmq.hpp>
#include <string>
#include <iostream>
#include <vector>

int main() {
	zmq::context_t contexto(1);
	zmq::socket_t router(contexto, zmq::socket_type::router);

	router.bind("tcp://*:5555");
	std::vector<zmq::message_t> parts;
	zmq::message_t part;

	std::cout << "Router preparado ..." << std::endl;

	while (true) {
		
		for (int i = 0; i < 3; i++) {
			router.recv(part);
			parts.push_back(std::move(part));
		}

		std::string client_id = parts[0].to_string();
		std::string msg = parts[2].to_string();
		std::cout << "Mensaje de : " << client_id << " : " << std::endl;

		router.send(zmq::buffer(client_id), zmq::send_flags::sndmore);
		router.send(zmq::message_t(), zmq::send_flags::sndmore);
		router.send(zmq::buffer("Respuesta del Servidor"), zmq::send_flags::none);
	}

	return 0;
}

