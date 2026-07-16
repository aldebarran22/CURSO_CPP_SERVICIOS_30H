// crow_cliente_cpr.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

int main()
{
    // Consumir servicio de crow con cpr:

    // Peticion GET:
    int id = 1;
    std::string sUrl = "http://localhost:8080/empleados/" + std::to_string(id);
    cpr::Url url{ sUrl };

    std::cout << "Peticion GET: " << sUrl << std::endl;
    cpr::Response resp = cpr::Get(url);
    
    std::cout << "Status: " << resp.status_code << std::endl;
    std::cout << "Body: " << resp.text << std::endl;

    // Peticion POST:
    std::string sUrl2 = "http://localhost:8080/empleados";
    cpr::Url url2{ sUrl2 };

    std::cout << "\nPeticion POST: " << sUrl2 << std::endl;   
    nlohmann::json j{ 
                       { "id", 13 }, 
                       { "nombre","Andres" }, 
                       { "cargo","Gerente" } 
    };

    cpr::Response resp2 = cpr::Post(
        url2,
        cpr::Header{ {"Content-type", "application/json"} },
        cpr::Body{j.dump()}
    );

    std::cout << "Status: " << resp2.status_code << std::endl;
    std::cout << "Body: " << resp2.text << std::endl;


    std::string sUrl3 = "http://localhost:8080/empleados";
    cpr::Url url3{ sUrl3 };

    std::cout << "\nPeticion GET: " << sUrl3 << std::endl;
    cpr::Response resp3 = cpr::Get(url3);

    std::cout << "Status: " << resp3.status_code << std::endl;
    std::cout << "Body: " << resp3.text << std::endl;
}
