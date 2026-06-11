#include <crow.h>
#include <nlohmann/json.hpp>

#include "PedidoCROW.h"

PedidoCROW::PedidoCROW(PedidoService&):service(service)
{
}

void PedidoCROW::run()
{
	
	// Configurar el servicio con las operaciones: GET / POST / PUT / DELETE
	crow::SimpleApp app;

	CROW_ROUTE(app, "/pedidos/<int>").methods(crow::HTTPMethod::GET)([this](int id) {

		try {
			// Verificar que existe:
			auto pedido = this->service.read(id);

			if (!pedido.has_value()) {
				// No hemos encontrado el pedido (ni en la cache ni en mysql)
				return crow::response(404, "Pedido con id: " + std::to_string(id) + " no existe");
			}

			// El pedido existe hay que devolverlo:
			json j = *pedido;
			return crow::response(j.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio (GET/id): ") + e.what());
		}
	});

	// Get - GET /pedidos
	CROW_ROUTE(app, "/pedidos").methods(crow::HTTPMethod::GET)([this]() {

		//std::lock_guard<std::mutex> lock(this->mtx);
		try {
			auto pedidos = this->service.selectAll();
			json j = pedidos;
			return crow::response(j.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio (GET): ") + e.what());
		}
		
	});

	// Puesta en marcha del servidor
	app.port(8082).concurrency(std::thread::hardware_concurrency()).
		multithreaded().
		run();
}

PedidoCROW::~PedidoCROW()
{
}
