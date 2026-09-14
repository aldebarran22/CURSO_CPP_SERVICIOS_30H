// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <thread>

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

    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

