// csv_json.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main()
{
	std::string pathIn = "..\\..\\practicas\\ficheros\\pedidos_final.csv";
	std::string pathOut = "..\\..\\practicas\\ficheros\\out\\pedidos.json";

	// Ficheros:
	std::ifstream fin(pathIn);
	std::ofstream fout(pathOut);

	std::string linea;
	std::vector<std::string> campos;
	std::vector<nlohmann::json> array;
	nlohmann::json doc;

	if (!fin) {
		std::cerr << "Fichero no encontrado: " << pathIn << std::endl;
		return 1;
	}



}

