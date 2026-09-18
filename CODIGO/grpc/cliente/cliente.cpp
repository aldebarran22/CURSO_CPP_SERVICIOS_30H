// cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "..\saludo.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

// Del fichero proto:
using saludo::Saludo;
using saludo::Solicitud;
using saludo::Respuesta;

// Clase cliente, mantiene un att. que representa el stub (del cliente)y se añade el método DiHola
class SaludoClient {
	std::unique_ptr<Saludo::Stub> stub_;

public:
	SaludoClient(std::shared_ptr<Channel> canal) : stub_(Saludo::NewStub(canal)) {}

	std::string DiHola(const std::string& nombre) {
		Solicitud solicitud;
		Respuesta respuesta;
		ClientContext contexto;

		solicitud.set_nombre(nombre);
		// Llamada al metodo rpc: 
		Status estado = stub_->DiHola(&contexto, solicitud, &respuesta);

		if (estado.ok()) {
			return respuesta.mensaje();
		}
		else {
			return "Error: " + estado.error_message();
		}
	}
};

int main()
{
	SaludoClient cliente(grpc::CreateChannel("localhost:50001", grpc::InsecureChannelCredentials()));
	std::string respuesta = cliente.DiHola("Mundo");
	std::cout << "Respuesta del servidor " << respuesta << std::endl;
	return 0;
}

