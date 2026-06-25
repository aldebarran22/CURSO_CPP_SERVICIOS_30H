// jwt_tokens.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include <crow.h>
#include <jwt-cpp/jwt.h>

using json = nlohmann::json;

// Credenciales:
#define USER "admin"
#define PWD "1234"

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& request) {

		auto j = json::parse(request.body);

		// Validar los campos que vienen en el json:
		if (!j.contains("user") || !j.contains("pwd")) {
			return crow::response(400, "json incorrecto, se esperaban campos login/pwd");
		}

		if (USER == j.at("user") && PWD == j.at("pwd")) {
			// Generamos el token:
			return crow::response("token generado");
		}
		else {
			return crow::response(401, "No existe el usuario");
		}

	});

	app.run();
}

