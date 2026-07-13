// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include <thread>
#include <string>

int main()
{
    // Objeto principal de crow: define operaciones y poner en marchar el server!
    crow::SimpleApp app;


    // Definir operaciones:
    // CROW_ROUTE(app, url/<tipo1>/<tipo2>).methods(...)([](tipo1 p1, tipo2 p2){cuerpo});

    CROW_ROUTE(app, "/")([]() {
        return "Hello World";
    });

    // Activar logs:


    // Poner en marcha el servidor:
    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}
