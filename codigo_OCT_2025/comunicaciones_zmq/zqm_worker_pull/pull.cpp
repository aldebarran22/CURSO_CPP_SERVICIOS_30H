#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::pull);

    std::cout << "Recibir datos ..." << std::endl;

    // Conectar:
    socket.connect("tcp://localhost:5557");

    while (true) {
        zmq::message_t mensaje;

        socket.recv(mensaje, zmq::recv_flags::none);
        std::cout << "Recibido: " << mensaje.to_string() << std::endl;
    }

    return 0;
}

