// conversor_csv_json.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main(){

    std::string pathIn = "..\\..\\..\\practicas\\ficheros\\pedidos_final.csv";
    std::string pathOut = "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json";

    std::ifstream fin(pathIn);
    std::ofstream fout(pathOut);

    std::string linea;
    std::vector<std::string> campos;
    bool cabs = true;

    // Una coleccion para almacenar los json de cada pedido:
    std::vector<nlohmann::json> array;
    nlohmann::json doc;


    if (!fin) {
        std::cerr << "No se ha encontrado el fichero: " << pathIn << std::endl;
        return 1;
    }

    while (std::getline(fin, linea)) {
        //std::cout << linea << std::endl;

        if (cabs) {
            cabs = false;

        }
        else {
            Pedido p(linea);
            array.push_back(p.to_json());
        }
    }
    fin.close();

    // Convertir y tabular;
    doc = array;

    // Imprimir a consola:
    std::cout << doc << std::endl;
    fout << doc.dump(4);

    fout.close();
    return 0;
}
