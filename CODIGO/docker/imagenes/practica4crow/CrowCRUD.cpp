#include "CrowCRUD.h"

CrowCRUD::CrowCRUD()
{
	// Inicializar la clave:
	this->siguiente_id = 1;
}

void CrowCRUD::run()
{
	crow::SimpleApp app; 

	// Create - POST /usuarios
	CROW_ROUTE(app, "/usuarios").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {

		CROW_LOG_INFO << "Operacion POST en usuarios";

		// Recoger el json que viene de la Request: el tipo es: crow::json::rvalue
		auto body = crow::json::load(req.body);
		if (!body) {
			// 400 Bad Request, el json no coincide con el json esperado:
			return crow::response(400, "Json incorrecto");
		}

		// Guardar el json enviado en el mapa: lo tenemos que hacer en  exclusion mutua;
		std::lock_guard<std::mutex> lock(mtx);
		int id = this->siguiente_id++;
		this->usuarios[id] = std::move(body); // ojo si copiamos no funciona bien, no se ven bien los datos.

		// Montamos la respuesta:
		crow::json::wvalue resp;
		resp["id"] = id;

		// 201: exito, para peticiones post
		return crow::response(201, resp);
	});

	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::GET)([this](int id) {

		CROW_LOG_INFO << "Operacion GET /id en usuarios, id = " << id;

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

		CROW_LOG_INFO << "Operacion GET en usuarios (" << usuarios.size() << ")";

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

		CROW_LOG_INFO << "Operacion PUT en el usuario id: " << std::to_string(id);

		// Todo ok, actualizamos el usuario:
		usuarios[id] = std::move(body);
		return crow::response(200, "Usuario actualizado");
	});


	CROW_ROUTE(app, "/usuarios/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {

		std::lock_guard<std::mutex> lock(this->mtx);
		if (this->usuarios.erase(id) == 0) {
			return crow::response(404, "Usuario con el id: " + std::to_string(id) + " no existe");
		}

		CROW_LOG_INFO << "Operacion DELETE en usuarios: id = " << id;

		// En la respuesta indicamos que va todo bien pero no tenemos contenido: 204
		crow::response resp;
		resp.code = 204;
		return resp;
	});

	// Configurar el nivel de Log: por defecto es INFO
	crow::logger::setLogLevel(crow::LogLevel::Info);

	// Puesta en marcha del servidor
	app.port(8080).multithreaded().run();
}

CrowCRUD::~CrowCRUD()
{
}
