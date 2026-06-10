// grpcCliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include "saludo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using saludo::Saludo;
using saludo::Solicitud;
using saludo::Respuesta;

// La clase del cliente mantiene un att que representa el _stub y añadimos un metodo para facilitar la comunicacion con el servidor
class SaludoClient { 

public:
    SaludoClient(std::shared_ptr<Channel> canal) : stub_(Saludo::NewStub(canal)){}

    std::string DiHola(const std::string& nombre) {
        Solicitud solicitud;
        Respuesta respuesta;
        ClientContext contexto;

        solicitud.set_nombre(nombre);

        // Hacemos la llamada al rcp: status representa el resultado de la peticion
        Status estado = stub_->DiHola(&contexto, solicitud, &respuesta);



    }

private:
    std::unique_ptr<Saludo::Stub> stub_;
};

int main()
{
    std::cout << "Hello World!\n";
}
