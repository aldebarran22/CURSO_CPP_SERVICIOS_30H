// crow_json_cliente.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

// Creadenciales del usuarios:
#define USER "admin"
#define PASS "1234"


using json = nlohmann::json;

int main()
{
	try {
		json j = { {"user", USER}, {"pass", PASS} };

		auto response = cpr::Post(
			cpr::Url{ "http://localhost:8080/login" },
			cpr::Header{ {"Accept", "application/json"} },
			cpr::Body{ j.dump() }
		);

		std::cout << "Respuesta de login: " << response.text << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << std::endl;
	}
}

