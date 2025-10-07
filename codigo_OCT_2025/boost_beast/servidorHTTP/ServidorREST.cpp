#include "ServidorREST.h"


ServidorREST::ServidorREST(net::io_context& ioc, unsigned short port) :ioc_(ioc), acceptor_(ioc, tcp::endpoint(tcp::v4(), port)) {}


void ServidorREST::run() {
	std::cout << "Servidor REST " << acceptor_.local_endpoint().port() << std::endl;

	for (;;) {
		tcp::socket socket(ioc_);
		acceptor_.accept(socket);
		handle_request(socket);
	}
}

void ServidorREST::handle_request(tcp::socket& socket) {
	beast::flat_buffer buffer;
	http::request<http::string_body> request;

	// Leer  la peticion:
	http::read(socket, buffer, request);

	// Imprimir la peticion:
	std::cout << "Peticion: " << request.target() << std::endl;
	std::cout << "Metodo: " << request.method_string() << std::endl; // post / get / delete etc.
	std::cout << "Body: " << request.body() << std::endl;
	std::cout << "-----" << std::endl;

	// La respuesta:
	http::response<http::string_body> response{ http::status::ok, request.version() };
	response.set(http::field::server, "RestApiServer/1.0");
	response.set(http::field::content_type, "application/json");

	// Conexion persistente:
	response.keep_alive(request.keep_alive());

	// Enrutamiento:
	if (request.method() == http::verb::post && request.target() == "/items") {
		// Peticion POST
		response.body() = this->peticionPost(request.body());
		
	}
	else if (request.method() == http::verb::get && request.target() == "/items") {
		// GET
		request.body() = this->peticionGet();

	}
	else if (request.method() == http::verb::delete_ && request.target().starts_with("/items/")) {
		// Delete
		std::string path = std::string(request.target());
		std::string id_str = path.substr(std::string("/items/").size());

		try {
			int id = std::stoi(id_str);
			request.body() = this->peticionDelete(id);

		}
		catch (...) {
			response.result(http::status::bad_request);
			response.body() = "Id incorrecto";
		}

	}
	else {
		// Error, si la verbo http y la url no coincide con las analizadas:
		response.result(http::status::not_found);
		response.body() = "Ruta no encontrada";
	}

	// Calcular y establecer automaticamente el encabezado: Content_length
	response.prepare_payload();
	http::write(socket, response);
}

std::string ServidorREST::peticionGet()
{
	json resp;

	for (const auto& [id, value] : this->items) {
		resp.push_back({ {"id", id}, {"value", value} });
	}

	return std::string();
}

std::string ServidorREST::peticionPost(const std::string body)
{
	return std::string();
}

std::string ServidorREST::peticionDelete(int id)
{
	return std::string();
}

