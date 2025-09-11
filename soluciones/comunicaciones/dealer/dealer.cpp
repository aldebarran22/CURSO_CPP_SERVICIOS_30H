#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
	zmq::context_t context(1);
	zmq::socket_t dealer(context, zmq::socket_type::dealer);

	std::cout << "Dealer preparado ... " << std::endl;

	dealer.setsockopt(zmq::sockopt::identity, "cliente1");
	

	dealer.connect("tcp://localhost:5555");

	dealer.send(zmq::buffer("Hola servidor"), zmq::send_flags::none);

	zmq::message_t reply;
	dealer.recv(reply);
	dealer.recv(reply); // delimitador vacío
	dealer.recv(reply);
	std::cout << "Respuesta: " << reply.to_string() << std::endl;

	return 0;
}