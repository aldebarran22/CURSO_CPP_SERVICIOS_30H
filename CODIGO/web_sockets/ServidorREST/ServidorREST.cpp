#include "ServidorREST.h"
// ServidorREST.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

ServidorREST::ServidorREST(net::io_context& ioc, unsigned int port) :ioc(ioc), acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {
	this->id = 1;
}

void ServidorREST::run() {
	// Bucle infinito donde estamos aceptando peticiones de los clientes:
	// crear un socket, 
	// acceptar una peticion
	// procesar la peticion

	std::cout << "Servidor REST: escuchando en el puerto " << acceptor.local_endpoint().port() << std::endl;

	for (;;) {
		// Crear el socket:
		tcp::socket socket(ioc);

		// Acceptar una peticion:
		acceptor.accept(socket);

		// procesar la peticion:
		procesarPeticion(socket);
	}
}

void ServidorREST::procesarPeticion(tcp::socket& socket) {
	beast::flat_buffer buffer;
	http::request<http::string_body> request;
	std::string mensaje = "";
	std::string metodo;

	try {
		// Leer la peticion:
		http::read(socket, buffer, request);

		// Extraer el mensaje y la querystring
		std::string target = request.target();
		metodo = request.method_string();

		std::cout << "Peticion: " << target << " metodo: " << metodo << std::endl;


		// Respuesta al cliente:
		http::response<http::string_body> response{ http::status::ok, request.version() };
		response.set(http::field::server, "REST API/1.0");
		response.set(http::field::content_type, "application/json");
		response.body() = "Respuesta del servidor: " + mensaje;

		// Conexion persistente:
		response.keep_alive(request.keep_alive());

		// Programar el enrutamiento: http://localhost:8080/items (POST)
		if (request.method() == http::verb::post && request.target() == "/items") {
			response.body() = this->peticionPOST(request.body());

		}
		// http://localhost:8080/items (GET)
		else if (request.method() == http::verb::get && request.target() == "/items") {
			response.body() = this->peticionGET();

		}  // http://localhost:8080/items/id (DELETE)
		else if (request.method() == http::verb::delete_ && request.target().starts_with("/items/")) {

			// Capturar el parámetro int que viene en la URL (target)
			std::string id_str = target.substr(std::string("/items/").size());

			// lanzar un error si no viene el id: 400 Bad_request
			try {
				int id = std::stoi(id_str);
				response.body() = this->peticionDELETE(id);

			}
			catch (...) {
				response.result(http::status::bad_request); // codigo 400
				response.body() = "Falta el id a borrar";
			}

		}
		else {
			response.result(http::status::not_found); // Error 404
			response.body() = "Ruta no encontrada";
		}


		// Calcular el tamaño de la respuesta: content_length
		response.prepare_payload();

		// Escribir respuesta:
		http::write(socket, response);
	}

	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}


std::string ServidorREST::peticionGET()
{
	// Devuelve todos los nombres de la colección
	json resp;

	for (const auto& [id, value] : this->items) {
		json aux = { {"id", id}, {"value", value} };
		resp.push_back(aux);
	}

	// Devolvemos el json como una cadena:
	return resp.dump();
}

std::string ServidorREST::peticionPOST(const std::string& body)
{
	json req = json::parse(body);

	// Validacion del json recibido:
	if (!req.contains("value") || !req["value"].is_string()) {
		json resp = {
			{"error", "Campo value obligatorio y debe ser un string"}
		};

		return resp.dump();
	}

	// Recuperar el value y cargarlo en la colección con la clave id generada:
	std::string value = req["value"];
	int id = this->id++;

	// Lo almacenamos en el mapa:
	this->items[id] = value;
	json resp = { {"id", id}, {"value", value} };

	return resp.dump();
}

std::string ServidorREST::peticionDELETE(int id)
{
	// Comprobar si existe el id en el mapa: con un iterator
	if (this->items.find(id) != this->items.end()) {
		this->items.erase(id);

		json resp = { {"id", id}, { "mensaje", "Item eliminado"} };
		return resp.dump();
	}
	else {
		// No existe el elemento:
		json resp = { {"id", id}, { "mensaje", "No existe el item"} };
		return resp.dump();
	}
}

ServidorREST::~ServidorREST()
{
}


