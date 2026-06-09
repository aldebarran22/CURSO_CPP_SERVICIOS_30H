// crow_basico.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
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

    // Configurar el servidor en el puerto 18000 y poner en marcha!
    app.port(18000).run();
}


int main()
{
    testCrow();
    return 0;
}
