// crow_cliente_cpr.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <cpr/cpr.h>

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
}
