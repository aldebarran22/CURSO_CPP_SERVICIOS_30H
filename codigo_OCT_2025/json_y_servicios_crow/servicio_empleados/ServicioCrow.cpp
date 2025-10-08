#include <crow.h>
#include <nlohmann/json.hpp>

#include "ServicioCrow.h"
using json = nlohmann::json;

ServicioCrow::ServicioCrow(EmpleadoService& service):service(service)
{
}

void ServicioCrow::iniciar()
{
	// Definir las rutas del servidor Rest:
	crow::SimpleApp app;

	CROW_ROUTE(app, "/empleados/<int>")([this](int id) {
		auto emp = this->service.obtenerEmpleado(id);
		if (!emp) {
			return crow::response(404, "Empleado " + std::to_string(id) + " no encontrado");
		}

		// Convertimos el objeto a json:
		crow::json::wvalue j;
		j["id"] = emp->id;
		j["nombre"] = emp->nombre;
		j["cargo"] = emp->cargo;

		crow::response(j);				

	});

	app.port(8080).multithreaded().run();
}

ServicioCrow::~ServicioCrow()
{
}
