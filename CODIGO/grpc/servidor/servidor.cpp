// servidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>

#include "saludo.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// Vienen del fichero .proto: namespace saludo --> package
using saludo::Saludo;
using saludo::Solicitud;
using saludo::Respuesta;

// Implementar una clase que hereda de Service y da contenido al método rpc DiHola:
class SaludoServiceImpl final : public Saludo::Service {

    Status DiHola(ServerContext* context, const Solicitud* request, Respuesta* response) override {

        // Recoger el nombre que viene de la solicitud:
        std::string nombre = request->nombre();

        // Montar el mensaje de Respuesta:
        response->set_mensaje("hola " + nombre);

        return Status::OK;
    }
};

int main()
{
    
}

