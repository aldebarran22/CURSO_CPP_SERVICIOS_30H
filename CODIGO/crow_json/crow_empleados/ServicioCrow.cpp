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

	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
		
		try {
			// Parsear el json:
			json j = json::parse(req.body);

			// Validacion de las etiquetas en el json:
			if (!j.contains("id") || !j.contains("nombre") || !j.contains("cargo")) {
				return crow::response(400, "Json incorrecto. Faltan etiquetas");
			}

			// Convertir el json en objeto Empleado:
			Empleado e = j.get<Empleado>();
			
			// Crear el empleado utilizado el service:
			if (this->service.create(e)) {
				return crow::response("Empleado "+e.nombre+" creado");
			}
			else {
				return crow::response(500, "No se ha podido crear el empleado");
			}

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string(e.what()));
		}
		
	});


	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
	
		try {
			auto empleado = this->service.read(id);
			if (empleado) {
				json doc = empleado;
				return crow::response(doc.dump());

			}
			else {
				return crow::response(404, std::string("El empleado: " + std::to_string(id) + " no existe"));
			}
		}
		catch (const std::exception& e) {
			return crow::response(500, std::string(e.what()));
		}
	});

	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::GET)([this]() {
		try {
			std::vector<Empleado> empleados = this->service.select();
			json doc = empleados;

			return crow::response(doc.dump(4));
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
