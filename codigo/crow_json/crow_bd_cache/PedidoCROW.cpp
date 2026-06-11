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
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}
	});

	// Get - GET /usuarios
	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {

		std::lock_guard<std::mutex> lock(this->mtx);

		// Definimos una estructura lista que se convierte a un array de json
		crow::json::wvalue lista = crow::json::wvalue::list();
		int i = 0;

		for (const auto& [id, usuario] : this->usuarios) {
			crow::json::wvalue item;
			item["id"] = id;

			if (usuario.has("nombre"))
				item["nombre"] = usuario["nombre"].s();
			else
				item["nombre"] = "";

			item["edad"] = usuario["edad"].i();

			// Cargar en la lista:
			lista[i++] = std::move(item);
		}


		// Definir la respuesta:
		crow::json::wvalue  resp;
		resp["usuarios"] = std::move(lista);
		return crow::response(resp);
		});
	*/
}

PedidoCROW::~PedidoCROW()
{
}
