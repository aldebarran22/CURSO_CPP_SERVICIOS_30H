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
			crow::response(404, "Usuario " + std::to_string(id) + " no encontrado");
		}

		// Los hemos encontrado:
		crow::json:wvalue res;

	});
	
	

}
CrowCRUD::~CrowCRUD() {

}
