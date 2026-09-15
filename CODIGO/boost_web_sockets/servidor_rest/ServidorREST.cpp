#include "ServidorREST.h"

ServidorREST::ServidorREST(net::io_context& ioc, unsigned int port):ioc(ioc),
acceptor(ioc, tcp::endpoint(tcp::v4(), port))
{
	this->id = 1;
}

void ServidorREST::run()
{
	std::cout << "Servidor REST escuchando en el puerto " << acceptor.local_endpoint().port()
		<< std::endl;

	while(true) {
		// Crear socket para recibir clientes:
		tcp::socket socket(ioc);

		// Aceptar peticiones:
		acceptor.accept(socket);
		std::cout << "Cliente conectado ..." << std::endl;

		// Procesar la peticion:
		procesarPeticion(socket);
	}
}

void ServidorREST::procesarPeticion(tcp::socket& socket)
{
	beast::flat_buffer buffer;
	http::request<http::string_body> request;
	std::string metodo;
	std::string target;

	try {
		// Leer la peticion del cliente:
		http::read(socket, buffer, request);

		// Extraer la URL y el metodo:
		target = request.target();
		metodo = request.method_string();

		std::cout << "Target: " << target << " Metodo: " << metodo << std::endl;

		// Preparar la respuesta al cliente, codigo de estado y la version del protocolo
		http::response<http::string_body> response{ http::status::ok, request.version() };
		response.set(http::field::server, "REST API 1.0");
		response.set(http::field::content_type, "text/plain"); // application/json
		response.body() = "Target pedido: " + target + " y metodo: " + metodo;

		// Conexion persistente;
		response.keep_alive(request.keep_alive());

		// ANALIZAR EL TARGET Y EL METODO:

		// Filtrar el target:
		if (request.method() == http::verb::post && target == "/items") {
			std::cout << "post /items" << std::endl;

		}

		else if (request.method() == http::verb::get && target == "/items") {
			std::cout << "get /items" << std::endl;
		}

		else if (request.method() == http::verb::delete_ && target == "/items") {
			std::cout << "delete /items" << std::endl;
		}

		else {
			// Control de errores:

			if (target != "/items") {
				// En este punto sabemos que la url no esta mapeada:
				response.result(http::status::not_found);
				response.body() = "Recurso no encontrado";
			}
			else {
				// No esta implementada la operacion:
				response.result(http::status::method_not_allowed);
				response.body() = "Método no implementado";
			}
		}

		// Calcular el tamaño de la respuesta:
		response.prepare_payload();

		// Escribir al cliente:
		http::write(socket, response);

	}
	catch (const std::exception& e) {
		std::cerr << "error: " << e.what() << std::endl;
	}
}


ServidorREST::~ServidorREST()
{
}
