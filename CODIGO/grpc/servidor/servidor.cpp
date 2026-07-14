// servidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <memory>

#include <grpcpp/grpcpp.h>
#include "..\saludo.grpc.pb.h"

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

void ejecutarServidor() {
    std::string direccion = "0.0.0.0:50001";

    // Construir el servidor, ponerlo en marcha y registrar el servicio:
    ServerBuilder builder;
    SaludoServiceImpl servicio;

    builder.AddListeningPort(direccion, grpc::InsecureServerCredentials());

    // Registrar el servicio:
    builder.RegisterService(&servicio);

    // Poner en marcha el servidor:
    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "Servidor escuchando en la direccion: " << direccion << std::endl;

    // Esperar conexiones:
    server->Wait();
}

int main()
{
    ejecutarServidor();
    return 0;
}
