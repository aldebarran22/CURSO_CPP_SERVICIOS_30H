// lib_crow.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <crow.h>
#include "CrowCRUD.h"


void testCrow() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "Hello world";
        });

    app.port(18080).run();
}

void testJsonCrow() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/json")([]() {
        crow::json::wvalue respuesta;
        respuesta["mensaje"] = "¡Hola desde Crow!";
        respuesta["estado"] = "ok";
        respuesta["codigo"] = 200;
        return crow::response{ respuesta };
        });

    app.bindaddr("127.0.0.1");
    app.port(8080);
    app.concurrency(2);
    app.run();
}

void testJsonCRUD() {
    CrowCRUD crowCRUD;
    crowCRUD.run();
}

int main()
{
    //testCrow();
    //testJsonCrow();
    testJsonCRUD();

    return 0;
}
