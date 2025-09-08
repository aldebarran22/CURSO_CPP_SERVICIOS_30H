#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

#include "CSVJson.h"
#include "Pedido.h"
#include "utilidades.h"


void CSVJson::conversorCSVToJson(std::string ficheroCSV, std::string ficheroJSON)
{
    std::ifstream fin(ficheroCSV);
    std::ofstream fout(ficheroJSON);

    std::string linea;
    std::vector<std::string> campos;
    bool cabs = true;
    std::vector<nlohmann::json> array;
    nlohmann::json grupo;

   
    if (!fin) {
        std::cerr << "No se ha encontrado el fichero: " << ficheroCSV << std::endl;
        return;
    }

    while (std::getline(fin, linea)) {
        //std::cout << linea << std::endl;

        if (cabs) {
            cabs = false;

        } else {
            Utilidades::split(linea, ';', campos);
            Pedido p(linea);
            array.push_back(p.to_json());
            campos.clear();                   
        }        
    }
    fin.close();

    // Convertir y tabular;
    grupo = array;

    // Imprimir a consola:
    //std::cout << grupo.dump(4) << std::endl;
    fout << grupo.dump(4) << std::endl;
    fout.close();
    
}

void CSVJson::conversorJsonCSV(std::string ficheroJSON)
{

}
