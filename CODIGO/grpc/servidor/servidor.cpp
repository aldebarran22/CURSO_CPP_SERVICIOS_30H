// servidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <grpcpp/grpcpp.h>

#include "saludo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Del fichero proto:
using saludo::Saludo;
using saludo::Solicitud;
using saludo::Respuesta;

// Clase que hereda de Service y da contenido al método virtual puro DiHola
class SaludoServiceImpl final : public Saludo::Service {

    Status DiHola(ServerContext* context, const Solicitud* request, Respuesta* response) override {
        // Programar nuestra logica de negocio en el metodo:

        // Recoger el nombre que viene de la solicitud:
        std::string nombre = request->nombre();

        // Montar el mensaje de respuesta:
        response->set_mensaje("hola " + nombre);

        return Status::OK;
    }

};



int main()
{
    std::cout << "Hello World!\n";
}
