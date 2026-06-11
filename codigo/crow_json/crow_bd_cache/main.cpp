// crow_bd_cache.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <crow.h>
#include <iostream>

int main()
{
	// Configurar el servicio con las operaciones: GET / POST / PUT / DELETE
	crow::SimpleApp app;

	CROW_ROUTE(app, "/pedidos/<int>").methods(crow::HTTPMethod::GET)([](int id) {

		

		// El usuario existe hay que devolverlo:
		crow::json::wvalue res;
		res["id"] = id;
		res["nombre"] = usuarios[id]["nombre"].s();
		res["edad"] = usuarios[id]["edad"].i();

		return crow::response(res);
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

}

