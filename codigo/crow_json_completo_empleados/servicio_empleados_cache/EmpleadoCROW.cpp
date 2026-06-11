#include <crow.h>
//#include <thread.h>
#include <nlohmann/json.hpp>

#include "EmpleadoCROW.h"

using json = nlohmann::json;

EmpleadoCROW::EmpleadoCROW(EmpleadoService& service):service(service)
{
}

void EmpleadoCROW::run() {
	crow::SimpleApp app;

	/*
	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, int id) {

		// Recuperamos el objeto json con load para hacer la validacion de la sintaxis:
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		try {

			// Para convertirlo directamente a objeto, utiliza nlohmann:
			json j = json::parse(req.body);
			//if (j.contains("id"))

			// Para convertirlo a objeto:
			Empleado emp = j.get<Empleado>();

			// Asegurar que el id de la URL y del objeto empleado es el mismo:
			if (emp.id != id) {
				return crow::response(400, "El ID del empleado no coincide con el del parametro");
			}

			// Verificar si el empleado existe en la BD:
			if (!this->repositorio.recuperarEmpleado(id)) {
				return crow::response(404, "El ID: "+std::to_string(id) + " del empleado no existe");
			}

			// Actualizamos los datos del empleado:
			this->repositorio.actualizar(emp);

			// Respuesta:
			crow::json::wvalue resul;
			resul["resultado"] = "Se ha actualizado el empleado correctamente";
			return crow::response(201, resul.dump());

			// return crow::response(204);  // Todo ok, pero sin contenido

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}

		});



	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::POST)([this](const crow::request& req) {

		// Recuperamos el objeto json con load para hacer la validacion de la sintaxis:
		auto body = crow::json::load(req.body);
		if (!body) {
			return crow::response(400, "Json incorrecto");
		}

		try {

			// Para convertirlo directamente a objeto, utiliza nlohmann:
			json j = json::parse(req.body);
			//if (j.contains("id"))

			// Para convertirlo a objeto:
			Empleado emp = j.get<Empleado>();

			// Insertar en la BD:
			this->repositorio.insertar(emp);

			crow::json::wvalue resul;
			resul["resultado"] = "Se ha creado el empleado correctamente";
			return crow::response(201, resul.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}

		});*/

	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::GET)([this](int id) {
		try {
			// Verificar que existe:
			auto empleado = this->service.read(id);

			if (!empleado.has_value()) {
				return crow::response(404, "Empleado con id: " + std::to_string(id) + " no existe");
			}

			// Aplica automaticamente la funcion: to_json (de objeto a json)
			json j = *empleado;
			return crow::response(j.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}

		});

	/*
	CROW_ROUTE(app, "/empleados").methods(crow::HTTPMethod::GET)([this]() {

		try {
			auto empleados = this->repositorio.listarTodos();
			json j = empleados; // El vector lo pasa a un array de json, y por cada objeto aplica: to_json
			return crow::response(j.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}
		});


	CROW_ROUTE(app, "/empleados/<int>").methods(crow::HTTPMethod::Delete)([this](int id) {

		try {
			// Verificar que existe:
			auto empleado = this->repositorio.recuperarEmpleado(id);

			if (!empleado.has_value()) {
				return crow::response(404, "Empleado con id: " + std::to_string(id) + " no existe");
			}

			// Eliminar de la BD:
			this->repositorio.eliminar(id);

			crow::json::wvalue resul;
			resul["resultado"] = "Se ha eliminado el empleado correctamente";
			return crow::response(200, resul.dump());

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string("Error en el servicio: ") + e.what());
		}

		});	

*/
	app.multithreaded().concurrency(std::thread::hardware_concurrency()).port(8000).run();
}

EmpleadoCROW::~EmpleadoCROW()
{
}
