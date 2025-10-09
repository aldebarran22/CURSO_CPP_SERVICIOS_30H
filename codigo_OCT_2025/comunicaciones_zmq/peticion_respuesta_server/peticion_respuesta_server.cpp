// peticion_respuesta_server.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <zmq.hpp>
#include <nlohmann/json.hpp>
#include "persona.hpp"

/*

auto response = cpr::Get(cpr::Url{"http://localhost:8080/empleados"});
	if (response.status_code == 200) {
		auto json = nlohmann::json::parse(response.text);
		std::cout << "Respuesta JSON: " << json.dump(2) << std::endl;
	} else {
		std::cerr << "Error: " << response.status_code << std::endl;
	}

*/

int main()
{
	zmq::context_t contexto(1);
	zmq::socket_t socket(contexto, zmq::socket_type::rep);

	// Hacer el bind al puerto:
	socket.bind("tcp://*:5555");

	std::cout << "Servidor zmq en el puerto 5555" << std::endl;
	while (true) {
		zmq::message_t request;

		// Esperamos el mensaje del cliente:
		socket.recv(request, zmq::recv_flags::none);

		nlohmann::json j = nlohmann::json::parse(request.to_string());
		Persona p = j.get<Persona>();

		std::cout << "Recibido Persona: " << p.nombre << " " << p.edad << std::endl;

		// Enviamos el mensaje al cliente:
		std::string respuesta = request.to_string();
		socket.send(zmq::buffer(respuesta), zmq::send_flags::none);
	}

	return 0;
}
