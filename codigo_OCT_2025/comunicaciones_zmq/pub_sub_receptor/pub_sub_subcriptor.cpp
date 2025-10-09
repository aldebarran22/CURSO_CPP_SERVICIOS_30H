// pub_sub_receptor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <zmq.hpp>
#include <iostream>

int main()
{
    zmq::context_t contexto(1);
    zmq::socket_t socket(contexto, zmq::socket_type::sub);
}
