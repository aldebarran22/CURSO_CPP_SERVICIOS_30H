// RL_router.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <zmq.hpp>
#include <string>

int main()
{
	zmq::context_t contexto(1);
	zmq::socket_t router(contexto, zmq::socket_type::router);

	router.bind("tcp://*:5555");
	zmq::message_t parte;
	std::vector<zmq::message_t> partes;
	int n = 2;

	std::cout << "Router preparado ..." << std::endl;
	while (true) {

		// Limpiar el vector antes de recibir:
		partes.clear();

		// Recibir las partes del mensaje:
		for (int i = 0; i < n; i++) {
			router.recv(parte);
			std::cout << "Parte[" << i << "] = " << parte.to_string() << std::endl;
			partes.push_back(std::move(parte));
		}

		std::string clienteId = partes[0].to_string();
		std::string payload = partes[1].to_string();

		std::cout << "Mensaje de " << clienteId << " " << payload << std::endl;

		// Respondemos al id del cliente
		router.send(zmq::buffer(clienteId), zmq::send_flags::sndmore); // Primera parte del mensaje
		router.send(zmq::buffer("respuesta del servidor"), zmq::send_flags::none); // la última parte
	}

	return 0;
}
