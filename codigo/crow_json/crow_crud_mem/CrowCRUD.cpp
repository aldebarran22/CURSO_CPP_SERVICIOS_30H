#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	this->siguiente_id = 1;
}

void CrowCRUD::run()
{
	// Configurar el servicio con las operaciones: GET / POST / PUT / DELETE
	crow::SimpleApp app;

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
		
		auto body = crow::json::load(req.body);

		// Si no me han enviado nada, generamos un error!
		if (!body) {
			return crow::response(400, "json incorrecto");
		}

		// Guardar el json en el mapa:
		int id = this->siguiente_id++;
		this->usuarios[id] = body; // OJO la copia no funciona, tiene que ser std::move

		// Montar la respuesta al cliente:
		crow::json::wvalue resp;
		resp["id"] = id;



		});

}

CrowCRUD::~CrowCRUD()
{
}
