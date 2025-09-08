// peticion_rest.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>



using namespace web;
using namespace web::http;
using namespace web::http::client;

int main() {
    try {
        // Crear cliente HTTP
        http_client client(U("https://jsonplaceholder.typicode.com"));

        // Realizar petición GET
        uri_builder builder(U("/users"));
        client.request(methods::GET, builder.to_string())
            .then([](http_response response) {
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();
            }
            else {
                throw std::runtime_error("Error en la respuesta HTTP");
            }
                })
            .then([](json::value jsonResponse) {
            // Imprimir cada usuario
            for (const auto& user : jsonResponse.as_array()) {
                std::wcout << L"Nombre: " << user.at(U("name")).as_string() << std::endl;
                std::wcout << L"Email: " << user.at(U("email")).as_string() << std::endl;
                std::wcout << L"---" << std::endl;
            }
                })
            .wait(); // Esperar a que termine la tarea
    }
    catch (const std::exception& e) {
        std::cerr << "Excepción: " << e.what() << std::endl;
    }

    return 0;
}
