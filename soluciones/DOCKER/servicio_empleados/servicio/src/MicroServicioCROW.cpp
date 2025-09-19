#include <crow.h>
#include "MicroServicioCROW.hpp"

MicroServicioCROW::MicroServicioCROW(EmpleadoService& service):service(service)
{
}

void MicroServicioCROW::iniciar()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/empleado/<int>")
	([this](int id) {
		auto emp = this->service.obtenerEmpleado(id);
		if (!emp) {
			return crow::response(404, "Empleado no encontrado ...");
		}

		// Para poder escribir la respuesta:
		crow::json::wvalue json;

		json["id"] = emp->id;
		json["nombre"] = emp->nombre;
		json["cargo"] = emp->cargo;
		
		return crow::response(json);
	});

	// Poner el servidor a la escucha!
	app.port(8000).multithreaded().run();
}

MicroServicioCROW::~MicroServicioCROW()
{
}
