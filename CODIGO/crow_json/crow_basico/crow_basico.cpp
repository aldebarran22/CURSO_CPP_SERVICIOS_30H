// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <crow.h>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main()
{
    crow::SimpleApp app;

    // CROW_ROUTE(app, url/<tipo>/<tipo>).methods(...)([lista_captura](parametros){cuerpo});

    CROW_ROUTE(app, "/")([]() {
        return "Hello World";
    });

    // Ejemplo para devolver una resp en json:
    CROW_ROUTE(app, "/info")([]() {

        crow::json::wvalue resp;

        resp["mensaje"] = "todo ok";
        resp["codigo"] = 200;

        // Devolver la respuesta al cliente:
        return crow::response{ resp }; // por defecto codigo HTTP es 200
     });


    // Recoger parámetros de la petición:
    CROW_ROUTE(app, "/operacion/<int>/<int>").methods(crow::HTTPMethod::GET)([](const crow::request& req, int a, int b) {

        crow::json::wvalue resp;

        int suma = a + b;
        resp["a"] = a;
        resp["b"] = b;
        resp["suma"] = suma;

        // Devolver la respuesta al cliente:
        return crow::response{ resp }; // por defecto codigo HTTP es 200
        });

    CROW_ROUTE(app, "/pedidos").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        // Recoger un pedido en formato json y imprimir algun dato del pedido:

        try {
            // Parsear el pedido en json con la libreria nlohmman:
            nlohmann::json j = nlohmann::json::parse(req.body);
            Pedido p = j.get<Pedido>();

            return crow::response("Pedido: " + std::to_string(p.idpedido));

        }
        catch (const std::exception& e) {
            return crow::response(500, "ERROR: " + std::string(e.what()));
        }
    });


    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

