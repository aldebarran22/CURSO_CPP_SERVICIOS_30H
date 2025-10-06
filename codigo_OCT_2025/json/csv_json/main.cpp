#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include "Conversor.h"


void strJson() {
    // Se define una cadena Raw: con formato json
    std::istringstream ss(R"({"nombre":"Ana","edad":28,"intereses":["programacion","musica","senderismo"]})");
    nlohmann::json doc;
    // Se convierte a json:
    ss >> doc;
    std::cout << "nombre: " << doc["nombre"] << std::endl;
    std::cout << doc.dump(4) << std::endl;
}

int main()
{
    strJson();

    //Conversor::conversorCSVToJson("..\\..\\..\\practicas\\ficheros\\pedidos_final.csv", "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json");
    return 0;
}

