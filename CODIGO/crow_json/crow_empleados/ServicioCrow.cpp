#include <crow.h>
#include <optional>
#include <thread>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "ServicioCrow.h"

using json = nlohmann::json;

ServicioCrow::ServicioCrow(EmpleadoService& service):service(service)
{
}

void ServicioCrow::run()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {});

	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
	
		auto empleado = this->service.read(id);
		if (empleado) {
			json doc = empleado;
			return crow::response(doc.dump());

		}
		else {
			return crow::response(404, std::string("El empleado: " + std::to_string(id) + " no existe"));
		}
	});

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency()).run();
}

ServicioCrow::~ServicioCrow()
{
}
