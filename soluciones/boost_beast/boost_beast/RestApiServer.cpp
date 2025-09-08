#include "RestApiServer.h"

RestApiServer::RestApiServer(boost::asio::io_context& ioc, unsigned short port):
	acceptor_(ioc, tcp::endpoint(tcp::v4(), port)) {
	std::cout << "Api REST escuchando en el puerto " << port << std::endl;
}

void RestApiServer::run() {
	std::cout << "Servidor HTTP escuchando en puerto: "
		<< acceptor_.local_endpoint().port() << "..." << std::endl;

	for (;;) {
		tcp::socket socket(this->acceptor_.get_executor());
		acceptor_.accept(socket);
		handle_request(socket);
	}
}

void RestApiServer::handle_request(tcp::socket& socket) {
	try {
		// La peticion:
		beast::flat_buffer buffer;
		http::request<http::string_body> req;
		http::read(socket, buffer, req);

		// La respuesta:
		http::response<http::string_body> res{
			http::status::ok, req.version() };
		res.set(http::field::server, "RestApiServer/1.0");
		res.set(http::field::content_type, "application/json");

		// Conexión persistente:
		res.keep_alive(req.keep_alive());

		// Enrutamiento basico:
		if (req.method() == http::verb::get && req.target() == "/items") {
			res.body() = this->route_get_items();

		} else if (req.method() == http::verb::post && req.target() == "/items") {
			res.body() = route_post_item(req.body());

		} else if (req.method() == http::verb::delete_ && req.target().starts_with("/items/")){
			std::string path = std::string(req.target());
			std::string id_str = path.substr(std::string("/items/").size());

			try {
				int id = std::stoi(id_str);
				res.body() = route_delete_item(id);
			} catch (...) {
				res.result(http::status::bad_request);
				res.body() = R"({"error":"Id incorrecto"})";
			}

		} else {
			res.result(http::status::not_found);
			res.body() = R"({"error":"Ruta no encontrada"})";
		}

		res.prepare_payload();
		http:write(socket, res);

	} catch (const std::exception& e) {
		std::cerr << "Error al procesar la petición " << e.what() << std::endl;
	}

}

std::string RestApiServer::route_get_items()
{
	json response;

	for (const auto& [id, value] : this->items_) {
		response.push_back({
			{"id", id},
			{"value", value}
			});
	}

	return response.dump();
}

std::string RestApiServer::route_post_item(const std::string& body)
{
	
	//Recibir el cuerpo de la petición HTTP (en formato JSON)
	//Extraer el contenido del nuevo elemento
	//Asignarle un ID único
	//Guardarlo en memoria (std::unordered_map<int, std::string>)
	//Devolver una respuesta JSON con el nuevo elemento creado
	

	try {
		// Parsear el cuerpo como JSON:
		json request = json::parse(body);

		// Validar que contiene el campo value:
		if (!request.contains("value") || !request["value"].is_string()) {
			json error = {
				{"error", "Campo 'value' requerido y debe ser texto"}
			};

			return error.dump();
		}

		// Extraer el valor de value y asignar un ID:
		std::string value = request["value"];
		int id = this->next_id_++;
		items_[id] = value;

		// Devolver la respuesta: en la respuesta se muestra el id generado!
		json response = {
			{"id", id},
			{"value", value}
		};

		return response.dump();
	}
	catch (const std::exception& e) {
		// Los errores también se genera en JSON:
		json error = {
			{"error", "JSON inválido"},
			{"detalles", e.what()}
		};
	}

	return std::string();
}

std::string RestApiServer::route_delete_item(int id)
{
	if (items_.find(id) != items_.end()) {
		// Se borra de la coleccion:
		items_.erase(id);
		json response = {
			{"status", "ok"},
			{"message", "Elemento eliminado"},
			{"id", id}
		};
		return response.dump();

	} else {
		json error = {
			{"error", "Elemento no encontrado"},
			{"id", id}
		};
		return error.dump();
	}
	
}
