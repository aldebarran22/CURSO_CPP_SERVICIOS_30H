#include <thread>

#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	this->siguiente_id = 1;
}

void CrowCRUD::run()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
		// Recibe un user, calcula el sig indice y lo coloca en la coleccion

		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "json incorrecto");
		}

		// Gardar el user en la coleccion:
		std::lock_guard<std::mutex> lock(this->mtx);
		int id = this->siguiente_id++;
		//this->usuarios[id] = body;  // OJO saca una copia!
		this->usuarios[id] = std::move(body);

		// Montar una respuesta al cliente:
		crow::json::wvalue resp;
		resp["id"] = id;
		return crow::response(201, resp);

	});

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {
		// Recuperar todos los usuarios de la colección:
		return "ok";
	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		// Recuperar un usuario de la colección:
		std::lock_guard<std::mutex> lock(this->mtx);

		// Comprobar si existe el usuario;
		if (this->usuarios.count(id) == 0) {
			// Recurso no encontrado!
			return crow::response(404, "Usuario id = " + std::to_string(id) + " no existe");
		}
		crow::json::wvalue resp;
		resp["id"] = id;
		resp["nombre"] = this->usuarios[id]["nombre"].s();
		resp["edad"] = this->usuarios[id]["edad"].i();

		return crow::response(resp);
	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {
		// Borrar un usuario de la colección:
		std::lock_guard<std::mutex> lock(this->mtx);

		// Comprobar si existe el usuario;
		if (this->usuarios.erase(id) == 0) {
			// Recurso no encontrado!
			return crow::response(404, "Usuario id = " + std::to_string(id) + " no existe");
		}

		crow::response respuesta;
		respuesta.code = 204;
		
		return respuesta;		
	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, int id) {
		// Recibe un user, calcula el sig indice y lo coloca en la coleccion
		return "ok";
	});

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency());
	app.run();
}

CrowCRUD::~CrowCRUD()
{
}
