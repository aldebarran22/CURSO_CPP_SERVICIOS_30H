
#include <iostream>
#include <zmq.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include "persona.hpp"

int main()
{
	try {
		// El cliente se conecta al mismo puerto:
		zmq::context_t contexto(1);

		zmq::socket_t socket(contexto, zmq::socket_type::req);
		socket.connect("tcp://localhost:5555");

		// Definir la persona:
		Persona p{ "Jose",59, true };

		// Convertir a json:
		nlohmann::json j = p;
		std::string mensaje = j.dump();

		// Enviar un mensaje al servidor:
		socket.send(zmq::buffer(mensaje), zmq::send_flags::none);

		zmq::message_t respuesta;
		socket.recv(respuesta, zmq::recv_flags::none);
		std::cout << "Respuesta del servidor: " << respuesta.to_string() << std::endl;

	}
	catch (std::exception& e) {
		std::cerr << "Error " << e.what() << std::endl;
	}

	return 0;
}

