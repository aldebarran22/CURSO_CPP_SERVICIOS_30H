// grpcServidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "saludo.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using saludo::Saludo;
using saludo::Solicitud;
using saludo::Respuesta;


class SaludoServiceImpl final : public Saludo::Service {
    // Hereda de Service y sobrescribe el metodo virtual DiHola, aqui implementamos 
    // la logica de lo que queremos hacer dentro del metodo rpc:
    Status DiHola(ServerContext* context, const Solicitud* request, Respuesta* reply) override {
        
        // El nombre de la peticion
        std::string nombre = request->nombre();

        // Montar el mensaje de salida:
        reply->set_mensaje("Hola " + nombre);

        return Status::OK;
    }

};



int main()
{
    
}

