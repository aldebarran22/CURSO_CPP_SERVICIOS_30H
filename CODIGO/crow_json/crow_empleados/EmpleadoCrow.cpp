#include <crow.h>
#include <optional>
#include <nlohmann/json.hpp>

#include "EmpleadoCrow.h"

using json = nlohmann::json;

EmpleadoCrow::EmpleadoCrow(EmpleadoService& service):service(service)
{
}

void EmpleadoCrow::run()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::GET)([this](int id) {

		auto empleado = this->service.read(id);
		if (empleado) {
			json doc = empleado;
			return crow::response(doc.dump());
		}
		else {
			return crow::response(404, std::string("El empleado con id: ") + std::to_string(id));
		}
	});

	app.port(8080).run();
}

EmpleadoCrow::~EmpleadoCrow()
{
}
