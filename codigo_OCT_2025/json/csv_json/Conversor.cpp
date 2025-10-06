#include <fstream>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include "Conversor.h"
#include "Utils.h"
#include "Pedido.h"

void Conversor::conversorCSVToJson(std::string path, std::string pathjson)
{
	std::ifstream fin;
	std::ofstream fout;


    std::string linea;
    std::vector<std::string> campos;
    bool cabs = true;
    std::vector<nlohmann::json> array;
    nlohmann::json grupo;


    if (!fin) {
        std::cerr << "No se ha encontrado el fichero: " << pathjson << std::endl;
        return;
    }

    while (std::getline(fin, linea)) {
        //std::cout << linea << std::endl;

        if (cabs) {
            cabs = false;

        }
        else {   

            Pedido p(linea);
            array.push_back(p.to_json());
            campos.clear();
        }
    }
    fin.close();

    grupo = array;

}
