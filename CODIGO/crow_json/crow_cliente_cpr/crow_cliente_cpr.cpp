// crow_cliente_cpr.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <string>

void test_crow_basico() {

    // Peticion GET a 
    int n1 = 10, n2 = 78;

    std::string sUrl = "http://localhost:18000/operacion/" + std::to_string(n1) + "/" + std::to_string(n2);
    cpr::Url url{ sUrl };

    std::cout << "Peticíon GET: " << sUrl << std::endl;
    cpr::Response resp = cpr::Get(url);

    std::cout << "Status: " << resp.status_code << std::endl;
    std::cout << "Body: " << resp.text << std::endl;
    
}

int main()
{
    test_crow_basico();
}

