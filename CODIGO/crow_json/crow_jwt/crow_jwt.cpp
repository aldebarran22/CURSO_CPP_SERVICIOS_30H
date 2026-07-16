// crow_jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <nlohmann/json.hpp>

#define USER "admin"
#define PASS "1234"

using json = nlohmann::json;

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& request) {
		try {
			// Recuperar el cuerpo de la peticion:
			auto j = json::parse(request.body);

			// Validar las etiquetas:
			if (!j.contains("user") || !j.contains("pass")) {
				return crow::response(400, "json incorrecto, se esperaban las credenciales");
			}

		}
		catch (const std::exception& e) {
			return crow::response(500, e.what());
		}
	});
}

