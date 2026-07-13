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
		
		// Recoger el json de la petición:
		auto body = crow::json::load(req.body);

		if (!body) {
			return crow::response(400, "json incorrecto");
		}

		// Guardar el usuario en el mapa (en memoria)
		// Bloquea hacia abajo
		std::lock_guard<std::mutex> lock(this->mtx);
		int id = this->siguiente_id++;
		this->usuarios[id] = std::move(body); // OJO, no copiar -> mover!!!

		// Montar la respuesta al cliente:
		crow::json::wvalue resp;
		resp["id"] = id;
		return crow::response(201, resp);

	});

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency()).run();
}

CrowCRUD::~CrowCRUD()
{
}
