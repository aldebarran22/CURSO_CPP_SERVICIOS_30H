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

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {
		// Definir una lista para volcar los usuarios:
		crow::json::wvalue lista = crow::json::wvalue::list();
		int i = 0;

		for (const auto& [id, usuario] : this->usuarios) {
			crow::json::wvalue item;
			item["id"] = id;

			if (usuario.has("nombre"))
				item["nombre"] = usuario["nombre"].s();
			else
				item["nombre"] = "";

			item["edad"] = usuario["edad"].i();

			// Cargar el item a la lista:
			lista[i++] = std::move(item);
		}

		// Montar la resp al cliente:
		crow::json::wvalue resp;
		resp["usuarios"] = std::move(lista);
		return crow::response(resp);


	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {

		std::lock_guard<std::mutex> lock(this->mtx);
		if (this->usuarios.erase(id) == 0) {
			return crow::response(404, "Usuario id: " + std::to_string(id) + " no existe");
		}

		crow::response resp;
		resp.code = 204; // borrado ok, pero sin contenido
		return resp;
	});

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency()).run();
}

CrowCRUD::~CrowCRUD()
{
}
