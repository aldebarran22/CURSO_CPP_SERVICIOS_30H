// jwt_tokens.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <crow.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <jwt-cpp/jwt.h>
#include <chrono>

#define USER "admin"
#define PWD "1234"

using json = nlohmann::json;

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/login")([](const crow::request& req) {

        try {
            auto j = json::parse(req.body);
            if (j.at("user") == USER && j.at("pwd") == PWD) {
                // Si es correcto podemos generar el token
                auto token = jwt::create().
                    set_issuer("curso C++").
                    set_payload_claim("usuario", jwt::claim(USER)).
                    set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes{ 30 }).
                    sign(jwt::algorithm::hs256{ PWD });

                // Devolver el token:
                crow::json::wvalue respuesta;
                respuesta["token"] = token;
                return crow::response(respuesta);
            }
        }
        catch (const std::exception& e) {
            return crow::response(400, std::string("Json incorrecto") + e.what());
        }
    });

}
