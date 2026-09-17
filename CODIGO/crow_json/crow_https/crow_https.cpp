// crow_https.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <crow.h>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return "ok desde https";
    });

    app.ssl_file("..\\certificados\\cert.pem", "..\\certificados\\key.pem").port(8443).multithreaded().run();
}

