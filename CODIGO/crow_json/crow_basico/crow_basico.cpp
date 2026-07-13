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
    // Objeto principal de crow: define operaciones y poner en marchar el server!
    crow::SimpleApp app;


    // Definir operaciones:
    // CROW_ROUTE(app, url/<tipo1>/<tipo2>).methods(...)([](tipo1 p1, tipo2 p2){cuerpo});

    CROW_ROUTE(app, "/")([]() {
        return "Hello World";
    });

    CROW_ROUTE(app, "/info")([]() {

        crow::json::wvalue resp;

        resp["mensaje"] = "todo ok";
        resp["codigo"] = 200;

        // Devolver la resp al cliente:
        return crow::response{ resp }; // por defecto es 200!
    });

    // Ejemplo con parametros:
    CROW_ROUTE(app, "/operacion/<int>/<int>").methods(crow::HTTPMethod::GET)([](int a, int b) {
        crow::json::wvalue resp;

        int suma = a + b;

        resp["a"] = a;
        resp["b"] = b;
        resp["suma"] = suma;

        return crow::response{ resp };
    });

    CROW_ROUTE(app, "/pedidos").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        // Recoger un pedido, validar un campo y devolver algún dato

        try {
            // Parsear el pedido con nlohmman:
            nlohmann::json j = nlohmann::json::parse(req.body);

            // Validar si viene o no un campo en el json:
            if (!j.contains("idpedido")) {
                return crow::response(400, "Falta el idpedido");
            }

            Pedido p = j.get<Pedido>();
        }
    });

    // Activar logs:


    // Poner en marcha el servidor:
    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}
