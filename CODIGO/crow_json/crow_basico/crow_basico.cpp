// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <crow.h>


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


    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

