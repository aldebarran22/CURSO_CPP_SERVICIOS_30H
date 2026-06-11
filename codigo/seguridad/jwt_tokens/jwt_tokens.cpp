// jwt_tokens.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <chrono>
#include <crow.h>

#include <nlohmann/json.hpp>
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

        // Validar que vienes los campos que necesitamos:
        if (!j.contains("user") || !j.contains("pwd")) {
            return crow::response(400, "json: incorrecto, se esperaban campos");
        }

        // Comprobar si existe o no el usuario:
        if (USER == j.at("user") && PWD == j.at("pwd")) {
            // Generar el token

        }
        else {
            return crow::response(400, "No existe el usuario");
        }
    });

    // Arrancar el servidor:
}

