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

    Status DiHola(ServerContext* context, const Solicitud* request, Respuesta* response) override {
        // Captura el nombre de la request:
        std::string nombre = request->nombre();
        response->set_mensaje("Hola " + nombre);
        return Status::OK;
    }
};

void ejecutarServidor() {
    std::string direccion = "0.0.0.0:50051";
    SaludoServiceImpl servicio;
    ServerBuilder builder;

    builder.AddListeningPort(direccion, grpc::InsecureServerCredentials());
    builder.RegisterService(&servicio);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Servidor on en: " << direccion << std::endl;
    server->Wait();
}


int main()
{
    ejecutarServidor();
    return 0;
}