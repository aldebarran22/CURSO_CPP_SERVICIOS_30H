
#include <iostream>


#include <crow.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <chrono>

#define USER "admin"
#define PWD "1234"

using json = nlohmann::json;

std::string sanitizer(const std::string& in) {
    // Limpiar caracteres especiales:

    std::string out;
    for (char c : in) {
        switch (c) {
        case '&': out += "&amp;"; break;
        case '<': out += "&lt;"; break;
        case '>': out += "&gt;"; break;
        case '"': out += "&quot;"; break;
        case '\'': out += "&#x27;"; break;
        case '/': out += "&#x2F;"; break;

        defaukt:
            out += c;
        }
    }

    return out;
}

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/login").methods("POST"_method)([](const crow::request& req) {

        try {
            auto j = json::parse(req.body);
            std::string nombre = sanitizer(j.at("nombre"));
            std::string apellidos = sanitizer(j.at("apellidos"));

            crow::json::wvalue respuesta;
            respuesta["nombre"] = nombre;
            respuesta["apellidos"] = apellidos;

            return crow::response(respuesta);
        }
        catch (const std::exception& e) {
            return crow::response(400, std::string("Json incorrecto") + e.what());
        }
        });

    //Poner el servidor a la escucha para http:
    app.port(8000).multithreaded().run();
}