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

    app.port(18000).multithreaded().concurrency(std::thread::hardware_concurrency());
    app.run();
}

