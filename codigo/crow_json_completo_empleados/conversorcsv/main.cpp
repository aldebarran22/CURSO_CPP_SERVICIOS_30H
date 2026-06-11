// conversorcsv.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include "Conversor.h"

void testJson() {
    nlohmann::json doc;

    doc["mensaje"] = "Hello World";
    std::cout << doc.dump(4) << std::endl;

}

void testPedidoJson() {
    Conversor::conversorCSVToJson("..\\..\\..\\practicas\\ficheros\\pedidos_final.csv",
        "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json");
}

int main()
{
    //testJson();
    testPedidoJson();
    return 0;
}
