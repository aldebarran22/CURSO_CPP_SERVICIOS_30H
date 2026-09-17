// crow_jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <string>
#include <nlohmann/json.hpp>
#include <jwt-cpp/jwt.h>

// Creadenciales del usuarios:
#define USER "admin"
#define PASS "1234"


using json = nlohmann::json;

int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::POST)([](const crow::request& req) {

		try {
			// Parsear el json:
			json j = json::parse(req.body);

			// Validacion de las etiquetas en el json:
			if (!j.contains("user") || !j.contains("pass")) {
				return crow::response(400, "Json incorrecto. Faltan etiquetas");
			}


		}
		catch (const std::exception& e) {
			return crow::response(500, std::string(e.what()));
		}
	});
}

