// cliente_jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

int main()
{
    try {
        std::string datos = "{\"user\":\"admin\",\"pwd\":\"1234\"}";

        auto response = cpr::Post(cpr::Url{ "http://localhost:8080/login" },
            cpr::Header{ {"Accept", "application/json"} },
            cpr::Body{ datos }
        );

        // Recoger respuesta:
        std::string respuesta = response.text;
        std::cout << respuesta << std::endl;

        json j = json::parse(respuesta);
        std::string token = j["token"];
        std::cout << "\nToken: " << token << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
