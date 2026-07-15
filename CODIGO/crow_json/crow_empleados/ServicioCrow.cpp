#include <crow.h>
#include <optional>
#include <thread>
#include <nlohmann/json.hpp>

#include "ServicioCrow.h"

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

	app.port(8080).multithreaded().concurrency(std::thread::hardware_concurrency()).run();
}

ServicioCrow::~ServicioCrow()
{
}
