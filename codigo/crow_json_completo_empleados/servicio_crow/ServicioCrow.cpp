#include "ServicioCrow.h"

#define PORT 8000

ServicioCrow::ServicioCrow()
{
	// Inicializar el indice de la coleccion:
	this->siguiente_id = 1;
}

void ServicioCrow::run() {
	crow::SimpleApp app;

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {
		
		// Recoger el usuario del cuerpo de la peticion:
		auto body = crow::json::load(req.body);

		// Si vienen errores de sintaxis, devuelve objeto vacio:
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		// Dar de alta el nuevo usuario:
		std::lock_guard<std::mutex> lock(this->mutex);
		int id = this->siguiente_id++;
		this->usuarios[id] = std::move(body); // Movemos en vez de copiar, si no, cambia codificación

		// Montar las respuesta para el cliente:
		crow::json::wvalue res;
		res["id"] = id;
		res["mensaje"] = "usuario creado";

		return crow::response(201, res);
	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, int id) {

		// Recoger el cuerpo de la petición:
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		// Actualizar el registro en la coleccion:
		std::lock_guard<std::mutex> lock(this->mutex);

		int n = this->usuarios.count(id);

		if (!n) {
			// Si no existe -> recurso no disponible
			return crow::response(404, "Usuario " + std::to_string(id) + " no encontrado");
		}

		// Machacar el usuarios con los nuevos datos:
		usuarios[id] = std::move(body);

		// Preparar la respuesta para el cliente:
		crow::json::wvalue res;
		res["id"] = id;
		res["mensaje"] = "Usuario actualizado";

		return crow::response(201, res);

		});

	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::GET)([this]() {
		std::lock_guard<std::mutex> lock(this->mutex);

		// Montar una lista con todos los usuarios del mapa:
		crow::json::wvalue lista = crow::json::wvalue::list();
		int i = 0;

		for (const auto& [id, usuario] : this->usuarios) {
			crow::json::wvalue item;
			item["id"] = id;

			// Comprobar si existe la clave nombre
			if (usuario.has("nombre")) {
				item["nombre"] = usuario["nombre"].s();
			}
			else {
				item["nombre"] = "";
			}

			if (usuario.has("email")) {
				item["email"] = usuario["email"].s();
			}
			else {
				item["email"] = "";
			}

			// Guardar el item en la lista:
			lista[i++] = std::move(item); // OJO, lo movemos no copiamos.
		}

		crow::json::wvalue res;
		res["usuarios"] = std::move(lista);
		return crow::response(res);

		});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {

		std::lock_guard<std::mutex> lock(this->mutex);
		int n = this->usuarios.count(id);

		if (!n) {
			// Si no existe -> recurso no disponible
			return crow::response(404, "Usuario " + std::to_string(id) + " no encontrado");
		}

		// Montar las respuesta para el cliente:
		crow::json::wvalue res;

		// Recuperar el usuario con la clave id
		crow::json::rvalue user = usuarios[id];
		CROW_LOG_INFO << "usuarios[id]: " << usuarios[id];

		res["id"] = id;
		res["nombre"] = user["nombre"].s(); // como string
		res["email"] = user["email"].s();

		return crow::response(res); // Si no ponemos código, se entiende 200

		});


	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {

		std::lock_guard<std::mutex> lock(this->mutex);

		if (usuarios.erase(id) == 0) {
			// Si no existe -> recurso no disponible
			return crow::response(404, "Usuario a borrar: " + std::to_string(id) + " no existe");
		}

		crow::response res;
		res.code = 204; // Operación realizada con exito pero no hay contenido
		return res;
		});


	CROW_ROUTE(app, "/info")([](const crow::request& req) {
		std::string agente = req.get_header_value("User-Agent");
		std::string param = req.url_params.get("id"); // /info?id=123
		return crow::response("Agente: " + agente + ", ID: " + param);
			});

	// Poner en marcha el servicio: multithreading con 4 hilos y log
	//app.port(PORT).multithreaded().concurrency(4).loglevel(crow::LogLevel::Debug).run();

	// Poner en marcha el servicio: multithreading con el numero de hilos del procesados y sin log:
	app.port(PORT).multithreaded().concurrency(std::thread::hardware_concurrency()).run();
}

ServicioCrow::~ServicioCrow()
{
}
