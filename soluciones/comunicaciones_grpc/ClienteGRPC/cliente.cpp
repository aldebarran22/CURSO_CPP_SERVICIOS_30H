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

class SaludoCliente {
public:
    SaludoCliente(std::shared_ptr<Channel> canal)
        : stub_(Saludo::NewStub(canal)) {
    }

    std::string DiHola(const std::string& nombre) {
        Solicitud solicitud;
        solicitud.set_nombre(nombre);

        Respuesta respuesta;
        ClientContext context;

        Status estado = stub_->DiHola(&context, solicitud, &respuesta);

        if (estado.ok()) {
            return respuesta.mensaje();
        }
        else {
            return "Error: " + estado.error_message();
        }
    }

private:
    std::unique_ptr<Saludo::Stub> stub_;
};

int main() {
    SaludoCliente cliente(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::string respuesta = cliente.DiHola("Mundo");
    std::cout << "Respuesta del servidor: " << respuesta << std::endl;
    return 0;
}
