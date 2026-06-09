// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <crow.h>

void testCrow() {
    crow::SimpleApp app;

    // CROW_ROUTE(app, url/<tipo1>/<tipo2>).methods( ...)([lista_captura](param1, param2){ cuerpo de la funcion })

    // Configuracion de rutas: si no se indica el metodo por defecto es GET
    CROW_ROUTE(app, "/")([]() {
        return "Hello World";
        });

    CROW_ROUTE(app, "/info")([]() {
        // Devolver una respuesta en json:
        crow::json::wvalue resp;

        resp["mensaje"] = "todo ok";
        resp["codigo"] = 200;

        // Devolver la respuesta al cliente:
        return crow::response{ resp };

        });

    // Ejemplo con parametros:
    CROW_ROUTE(app, "/operacion/<int>/<int>").methods(crow::HTTPMethod::GET)([](const crow::request& req, int a, int b) {
        // Devolver una respuesta en json:
        crow::json::wvalue resp;

        int suma = a + b;
        resp["a"] = a;
        resp["b"] = b;
        resp["suma"] = a + b;

        return crow::response{ resp };
        });

    // Configurar el servidor en el puerto 18000 y poner en marcha!
    app.port(18000);
       
    app.multithreaded();

    // Elegir el numero de hilos:
    app.concurrency(std::thread::hardware_concurrency());

    app.run();
}


int main()
{
    testCrow();
    return 0;
}
