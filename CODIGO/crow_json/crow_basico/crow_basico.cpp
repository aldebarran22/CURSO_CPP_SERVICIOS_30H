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

    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

