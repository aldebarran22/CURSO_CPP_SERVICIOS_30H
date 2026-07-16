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

    std::cout << "Peticion POST: " << sUrl2 << std::endl;   
    nlohmann::json j{ 
                       { "id", 12 }, 
                       { "nombre","Juan" }, 
                       { "cargo","Gerente" } };
}

    cpr::Response resp2 = cpr::Post(url2,
        cpr::Header{ {"Content-type", "application/json"} },
        cpr::Body{j.dump()});

    std::cout << "Status: " << resp2.status_code << std::endl;
    std::cout << "Body: " << resp2.text << std::endl;
}
