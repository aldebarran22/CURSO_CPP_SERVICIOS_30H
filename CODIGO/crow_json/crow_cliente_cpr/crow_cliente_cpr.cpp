// crow_cliente_cpr.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include <string>

void test_crow_basico() {

    // Peticion GET 
    int n1 = 10, n2 = 78;

    std::string sUrl = "http://localhost:18000/operacion/" + std::to_string(n1) + "/" + std::to_string(n2);
    cpr::Url url{ sUrl };

    std::cout << "Peticion GET: " << sUrl << std::endl;
    cpr::Response resp = cpr::Get(url);

    std::cout << "Status: " << resp.status_code << std::endl;
    std::cout << "Body: " << resp.text << std::endl;
    
    
    // Peticion POST:
    std::string sUrl2 = "http://localhost:18000/pedidos";
    cpr::Url url2{ sUrl2 };

    std::cout << "Peticion POST: " << sUrl2 << std::endl;
    nlohmann::json j{
        {"id_pedido", "12345"},
        {"cliente" , "NCH"},
        {"empleado" , "Jorge"},
        {"empresa" , "Indra"},
        {"importe" , 250.0},
        {"pais" , "España"}
    };

    cpr::Response resp2 = cpr::Post(url2,
        cpr::Header {{"Content-type", "application/json"}},
        cpr::Body{ j.dump() }
    );

    std::cout << "Status2: " << resp2.status_code << std::endl;
    std::cout << "Body2: " << resp2.text << std::endl;
}

int main()
{
    test_crow_basico();
}

