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

    });

    // Arrancar el servidor:
}

