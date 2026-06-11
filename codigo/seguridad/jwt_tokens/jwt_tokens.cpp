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

        try {
            auto j = json::parse(request.body);

            // Validar que vienes los campos que necesitamos:
            if (!j.contains("user") || !j.contains("pwd")) {
                return crow::response(400, "json: incorrecto, se esperaban campos");
            }

            // Comprobar si existe o no el usuario:
            if (USER == j.at("user") && PWD == j.at("pwd")) {
                // Generar el token
                auto token = jwt::create().
                    set_issuer("curso C++").
                    set_payload_claim("usuario", jwt::claim(std::string(USER))).
                    set_expires_at(std::chrono::system_clock::now() + std::chrono::minutes{ 30 }).
                    sign(jwt::algorithm::hs256{ PWD });

                // Devolver el token:
                crow::json::wvalue respuesta;
                respuesta["token"] = token;
                return crow::response(respuesta);
            }
            else {
                return crow::response(401, "No existe el usuario");
            }
        }
        catch (const std::exception& e) {
            return crow::response(500, "Error: " + std::string(e.what()));
        }
    });

    CROW_ROUTE(app, "/info").methods("GET"_method)([]() {

        try {
            crow::json::wvalue respuesta;
            respuesta["resul"] = "ok";
            return crow::response(respuesta);
        }
        catch (const std::exception& e) {
            return crow::response(500, "Error: " + std::string(e.what()));
        }

    });
    
    CROW_ROUTE(app, "/app").methods("GET"_method)([](const crow::request& request) {

        try {
            auto auth_header = request.get_header_value("Authorization");
            std::cout << "Authorization: " << auth_header << std::endl;
           
            // Verificar que el encabezado exista y comience con "Bearer "
            if (auth_header.substr(0, 7) != "Bearer ") {
                return crow::response(401, "Token no proporcionado o mal formado");
            }
           

            // Extraer el token
            std::string token = auth_header.substr(7);
            std::cout << "Token: " << token << std::endl;


            crow::json::wvalue respuesta;
            respuesta["resul"] = "ok";
            return crow::response(respuesta);
        }
        catch (const std::exception& e) {
            return crow::response(500, "Error: " + std::string(e.what()));
        }
        });
        

    // Arrancar el servidor por HTTP:
    //app.multithreaded().concurrency(std::thread::hardware_concurrency()).port(8000).run();

    // Arrancar el servidor por HTTPS:
    app.ssl_file("..\\certificados\\cert.pem", "..\\certificados\\key.pem").port(443).run();

}

