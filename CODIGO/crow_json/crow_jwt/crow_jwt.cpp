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
					set_expires_at(std::chrono::system_clock::now() + std::chrono::seconds{ 10 }).
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

	CROW_ROUTE(app, "/app").methods(crow::HTTPMethod::GET)([](const crow::request& req) {
		try {
			// Extraer el token de la cabecera:
			auto auth_header = req.get_header_value("Authorization");
			std::cout << "Authorization: " << auth_header << std::endl;

			if (auth_header == "" || auth_header.substr(0, 7)!= "Bearer ") {
				return crow::response(401, "No autorizado");
			}

			std::string token = auth_header.substr(7);
			std::cout << "Token: " << token << std::endl;

			// Decodificar el token
			auto token_dec = jwt::decode(token);

			// Configurar las opciones para verificar el token:
			auto verifier = jwt::verify()
				.allow_algorithm(jwt::algorithm::hs256{ PASS })
				.with_issuer("curso c++");

			verifier.verify(token_dec);

			// Extraer campos:
			std::string usuario = token_dec.get_payload_claim("usuario").as_string();
			std::cout << "usuario: " << usuario << std::endl;

			crow::json::wvalue resp;
			resp["usuario"] = "peticion de " + usuario;
			return crow::response(resp);

		}
		catch (const std::exception& e) {
			return crow::response(500, std::string(e.what()));
		}
	});

	app.port(8080).multithreaded().run();
}

