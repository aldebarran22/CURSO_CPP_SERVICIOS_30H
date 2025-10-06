#include "CrowCRUD.h"


CrowCRUD::CrowCRUD() {
	this->siguiente_id = 1;
}

void CrowCRUD::run() {
	// Definir el servicio, con las operaciones y arrancar el servidor:
	crow::SimpleApp app;

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {

		// Recoger del cuerpo de la peticion el json (usuario)
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		// Dar de alta el usuario en la coleccion:
		std::lock_guard<std::mutex> lock(mtx);
		int id = this->siguiente_id++;
		usuarios[id] = body;

		// Montar la respuesta al cliente:
		crow::json::wvalue res;
		res["id"] = id;
		res["mensaje"] = "usuario creado";

		return crow::response(201, res);

	});
	

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		std::lock_guard<std::mutex> lock(this->mtx);
		int n = this->usuarios.count(id);

		std::cout << "Numero de usuarios: " << n << " usuarios" << std::endl;

		// Chequear si hemos encontrado la clave:
		if (!n) {
			// Si no lo encontramos:
			return crow::response(404, "Usuario " + std::to_string(id) + " no encontrado");
		}

		// Lo hemos encontrado devolvemos nombre y email
		crow::json::wvalue res;
		res["nombre"] = usuarios[id]["nombre"].s();
		res["email"] = usuarios[id]["email"].s();

		return crow::response(res);

	});
	
	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {
		std::lock_guard<std::mutex> lock(this->mtx);

		if (usuarios.erase(id) == 0)
			return crow::response(404, "Usuario " + std::to_string(id) + " no encontrado");

		// Devolvemos solo el código 204, no tiene contenido, pero si exito
		crow::response res;
		res.code = 204;
		return res;
	});

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {
		std::lock_guard<std::mutex> lock(this->mtx);

		// Montar una lista con todos los usuarios:
		crow::json::wvalue lista = crow::json::wvalue::list();
		int i = 0;

		for (const auto& [id, usuario] : usuarios) {
			crow::json::wvalue item;
			item["id"] = id;

			if (usuario.has("nombre"))
				item["nombre"] = usuario["nombre"].s();
			else
				item["nombre"] = "";

			if (usuario.has("email"))
				item["email"] = usuario["email"].s();
			else
				item["email"] = "";

			lista[i++] = std::move(item);
		}

		crow::json::wvalue res;
		res["usuarios"] = std::move(lista);
		return crow::response(res);

	});
}
CrowCRUD::~CrowCRUD() {

}
