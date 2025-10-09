// pub_sub_publisher.cpp : Enviar datos cada segundo a los subcriptores
//
#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>


int main()
{
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::pub);
    socket.bind("tcp://*:5556");

    std::srand(std::time(nullptr));

    std::string mensaje;
    int valor;
    std::string medidas[] = { "temperatura", "humedad", "viento" };

    while (true) {

        for (std::string m : medidas) {
            valor = std::rand() % 100;
            mensaje = m + " " + std::to_string(valor);

            socket.send(zmq::buffer(mensaje));
            std::cout << "Publicando: " << mensaje;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    return 0;    
}
