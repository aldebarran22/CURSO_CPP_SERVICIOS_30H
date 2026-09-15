// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <thread>
#include <string>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main()
{
    // Objeto principal:
    crow::SimpleApp app;

    // Definir operaciones dentro del servicio:
    // CROW_ROUTE(app, url/<tipo1>/<tipo2>).methods(...)([](tipo1 p1, tipo2 p2){cuerpo});

    CROW_ROUTE(app, "/")([]() { // por defecto es GET
        return "Hello World";
    });

    // Ejemplo con parametros: http://localhost:18000/operacion?p1=7&p2=9
    CROW_ROUTE(app, "/operacion/<int>/<int>").methods(crow::HTTPMethod::GET)([](int a, int b) {
        crow::json::wvalue resp;

        int suma = a + b;
        resp["a"] = a;
        resp["b"] = b;
        resp["resul"] = suma;
        return crow::response{ resp };
    });

    CROW_ROUTE(app, "/operacion").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        crow::json::wvalue resp;

        // Recoger lo que viene del cuerpo de la peticion:
        auto datos = crow::json::load(req.body);

        if (!datos) {
            return crow::response(400); // Bad request, json incompleto!
        }
        int a = datos["a"].i(); // int
        int b = datos["b"].i(); // int

        int suma = a + b;       
        resp["resul"] = suma;
        return crow::response{ resp };
        });

    // Recoger un pedido con una operación post, conversión automática  entre JSON -> Pedido
    // Validar etiquetas en el Json:
    CROW_ROUTE(app, "/pedidos").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        crow::json::wvalue resp;

        try {
            // Parsear el json con la lib. nlohmman: valida la sintaxis
            nlohmann::json j = nlohmann::json::parse(req.body);

            // Validación de los campos:
            if (!j.contains("idpedido") || !j.contains("cliente")) {
                CROW_LOG_ERROR << "Faltan etiquetas obligatorias";
                return crow::response(400, "Faltan etiquetas obligatorias");
            }

            // Conversión de json a objeto Pedido:
            Pedido p = j.get<Pedido>(); // lanza: from_json

            // Conversión de objeto Pedido a json:
            nlohmann::json j2 = p; // lanza to_json

            CROW_LOG_INFO << j2.dump();
            return crow::response(j2.dump(4));
        }
        catch (const std::exception& e) {
            CROW_LOG_ERROR << "Error: " << e.what();
            return crow::response(500, "ERROR: " + std::string(e.what()));
        }

    });

    // Activar mensajes de log:
    // crow::logger::setLogLevel(crow::LogLevel::Debug);

    app.port(18000).
        multithreaded().
        concurrency(std::thread::hardware_concurrency()).
        loglevel(crow::LogLevel::Debug);

    app.run();
}

