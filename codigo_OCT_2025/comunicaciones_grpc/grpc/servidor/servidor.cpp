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


int main()
{
    return 0;
}