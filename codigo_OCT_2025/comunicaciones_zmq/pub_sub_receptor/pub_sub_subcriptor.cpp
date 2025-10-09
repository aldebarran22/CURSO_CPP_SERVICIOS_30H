// pub_sub_receptor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <zmq.hpp>
#include <iostream>

int main()
{
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::sub);

    socket.connect("tcp://localhost:5556");

    // Para filtrar por un topic:
    socket.set(zmq::sockopt::subscribe, "viento");

    while (true) {
        zmq::message_t msg;

        socket.recv(msg);
        std::string medida = msg.to_string();

        std::cout << "Recibido: " << medida << std::endl;

    }

    return 0;
}
