#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	this->siguiente_id = 1;
}

void CrowCRUD::run()
{
	// Configurar el servicio con las operaciones: GET / POST / PUT / DELETE
	crow::SimpleApp app;

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
		
		auto body = crow::json::load(req.body);

		// Si no me han enviado nada, generamos un error!
		if (!body) {
			return crow::response(400, "json incorrecto");
		}

		// Guardar el json en el mapa:
		std::lock_guard<std::mutex> lock(mtx);
		// Se ejecuta en exclusión mutua, solo modifica 1 hilo
		int id = this->siguiente_id++;
		this->usuarios[id] = std::move(body); // OJO la copia no funciona, tiene que ser std::move

		// Montar la respuesta al cliente:
		crow::json::wvalue resp;
		resp["id"] = id;

		return crow::response(201, resp);

		});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {

		std::lock_guard<std::mutex> lock(this->mtx);
		if (this->usuarios.erase(id) == 0) {
			return crow::response(404, "Usuario id: " + std::to_string(id) + " no existe");
		}

		crow::response resp;
		resp.code = 204;
		return resp;
		});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		
		std::lock_guard<std::mutex> lock(this->mtx);
		if (this->usuarios.count(id) == 0) {
			return crow::response(404, "Usuario con el id: " + std::to_string(id) + " no existe");
		}

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

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, int id) {

		std::lock_guard<std::mutex> lock(this->mtx);

		// Recoger el json que viene de la Request: el tipo es: crow::json::rvalue
		auto body = crow::json::load(req.body);
		if (!body) {
			// 400 Bad Request, el json no coincide con el json esperado:
			return crow::response(400, "Json incorrecto");
		}

		// Controlar si existe o no el id en la coleccion:
		if (usuarios.count(id) == 0) {
			return crow::response(404, "Usuario con el id: " + std::to_string(id) + " no existe");
		}
		
		// Todo ok, actualizamos el usuario:
		usuarios[id] = std::move(body);
		return crow::response(200, "Usuario actualizado");
		});

	// Puesta en marcha del servidor
	app.port(8080).concurrency(std::thread::hardware_concurrency()).multithreaded().run();


}


CrowCRUD::~CrowCRUD()
{
}
