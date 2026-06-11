// cliente_jwt.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

int main()
{
    std::string datos = "{\"user\":\"admin\",\"pwd\" : \"1234\"}";

    // Peticion POST:
    try {
        auto response = cpr::Post(cpr::Url{ "http://localhost:8000/login" },
            cpr::Header{ {"Accept","application/json"} },
            cpr::Body{ datos });

        // Respuesta:
        std::string respuesta = response.text;
        std::cout << respuesta << std::endl;

        json j = json::parse(respuesta);
        std::string token = j["token"];
        std::cout << "\nToken: " << token << std::endl;

        // Reenviar el token por una peticion GET:
        std::string cadena = "Bearer " + token;

        auto response2 = cpr::Get(cpr::Url{ "http://localhost:8000/app" },
            cpr::Header{ {"Authorization",cadena} });
        std::string respuesta2 = response2.text;
        std::cout << "\nSegundo mensaje: " << respuesta2 << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
}
