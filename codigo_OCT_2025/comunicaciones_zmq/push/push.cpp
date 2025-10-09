#include <iostream>
#include <zmq.hpp>
#include <string>

int main()
{
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::push);

    std::cout << "Enviar tareas ..." << std::endl;

    // Hacer el bind al puerto:
    socket.bind("tcp://*:5557");
    for (int i = 0; i < 10; i++) {
        socket.send(zmq::buffer("Tarea: " + std::to_string(i + 1)), zmq::send_flags::none);
    }

    return 0;

}
