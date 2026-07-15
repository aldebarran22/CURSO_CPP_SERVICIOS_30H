#include <crow.h>
#include <optional>
#include <thread>
#include <nlohmann/json.hpp>

#include "ServicioCrow.h"

using json = nlohmann::json;


ServicioCrow::ServicioCrow(EmpleadoService& service):service(service)
{
}

void ServicioCrow::run()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::GET)([this](int id) {

		auto empleado = this->service.read(id);
		if (empleado) {
			json doc = empleado;
			return crow::response(doc.dump());
		}
		else {
			return crow::response(404, std::string("El empleado con id: " + std::to_string(id)));
		}
	});

	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {

		try {
			// Recoger el json de la petición:
			auto j = json::parse(req.body);

			// Validacion del json:
			if (!j.contains("id") || !j.contains("nombre") || !j.contains("cargo")) {
				return crow::response(400, "Json incorrecto. Faltan etiquetas");
			}

			Empleado e = j.get<Empleado>();
			if (this->service.create(e)) {
				return crow::response("Empleado creado");
			}
			else {
				return crow::response(500, "Empleado no creado");
			}
		}
		catch (const std::exception& e) {
			return crow::response(500, std::string(e.what()));
		}
	});

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency()).run();
}

ServicioCrow::~ServicioCrow()
{
}
