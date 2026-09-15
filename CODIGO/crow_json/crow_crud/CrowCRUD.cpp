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

	});

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {
		// Recuperar todos los usuarios de la colección:

	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		// Recuperar un usuario de la colección:

	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {
		// Borrar un usuario de la colección:

	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, int id) {
		// Recibe un user, calcula el sig indice y lo coloca en la coleccion

	});

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency());
	app.run();
}

CrowCRUD::~CrowCRUD()
{
}
