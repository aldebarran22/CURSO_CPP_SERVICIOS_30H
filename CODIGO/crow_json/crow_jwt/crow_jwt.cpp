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

			// Validar user / pass:
			if (USER == j.at("user") && PASS == j.at("pass")) {

				// Generar esta el usuario validado se genera el token.
				auto token = jwt::create().
					set_issuer("curso c++").
					set_payload_claim("usuario", jwt::claim(std::string(USER))).
					set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{ 30 }).
					sign(jwt::algorithm::hs256{ PASS });

				// Generar la respuesta con el token al cliente:
				crow::json::wvalue respuesta;
				respuesta["token"] = token;
				return crow::response(respuesta);

			}
			else {
				return crow::response(403, "Se requieren credenciales");
			}
		}
		catch (const std::exception& e) {
			return crow::response(500, std::string(e.what()));
		}
	});

	app.port(8080).multithreaded().run();
}

