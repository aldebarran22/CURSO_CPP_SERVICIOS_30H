// conversor_csv_json.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main()
{
    std::string pathIn = "..\\..\\..\\practicas\\ficheros\\pedidos_final.csv";
    std::string pathOut = "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json";

    std::ifstream fin(pathIn);
    std::ofstream fout(pathOut);

    std::string linea;
    std::vector<std::string> campos;
    bool cabs = true;


    if (!fin) {
        std::cerr << "No se ha encontrado el fichero: " << pathIn << std::endl;
        return;
    }

    while (std::getline(fin, linea)) {
        std::cout << linea << std::endl;

        if (cabs) {
            cabs = false;

        }
        else {            
            Pedido p(linea);

        }
    }
    fin.close();

    // Convertir y tabular;

    // Imprimir a consola:


    fout.close();
    return 0;
}
