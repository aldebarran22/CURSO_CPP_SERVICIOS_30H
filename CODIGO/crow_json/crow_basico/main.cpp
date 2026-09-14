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

    CROW_ROUTE(app, "/")([]() {
        return "Hello World";
    });

    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

