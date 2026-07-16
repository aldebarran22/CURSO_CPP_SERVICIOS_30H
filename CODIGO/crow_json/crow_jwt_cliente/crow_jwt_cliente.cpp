// crow_jwt_cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

int main()
{
	try {
		// El cliente hace una peticion /login al servicio y guarda el token para enviarlo en sucesivas peticiones
		json j = { {"user","admin"}, {"pass", "1234"} };

		auto response = cpr::Post(
			cpr::Url{ "http://localhost:8080/login" },
			cpr::Header{ {"Accept", "application/json"} },
			cpr::Body{ j.dump() }
		);

		// Recoger respuesta:
		std::string respuesta = response.text;
		std::cout << "Respuesta: " << respuesta << std::endl;

		// Pasear la respuesta a json:
		json jresp = json::parse(respuesta);
		std::string token = jresp.at("token");
		std::cout << "\n\nToken: " << token << std::endl;


		// Detenerlo 2 minutos:
		std::this_thread::sleep_for(std::chrono::minutes{ 2 });


		// Hacer una segunda peticion al Servidor: enviando el token a un recurso protegido:
		std::string cadena = "Bearer " + token;

		auto response2 = cpr::Get(
			cpr::Url{ "http://localhost:8080/app" },
			cpr::Header{{"Authorization", cadena}}
		);

		std::string respuesta2 = response2.text;
		std::cout << "\nPeticion: app " << respuesta2 << std::endl;

	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

