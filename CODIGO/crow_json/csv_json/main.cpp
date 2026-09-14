// csv_json.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main()
{
	std::string pathIn = "..\\..\\..\\practicas\\ficheros\\pedidos_final.csv";
	std::string pathOut = "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json";

	std::ifstream fin(pathIn);
	std::ofstream fout(pathOut);

	std::vector<nlohmann::json> array;
	nlohmann::json doc;
	bool cabs = true;
	std::string linea;

	while (std::getline(fin, linea)) {
		std::cout << linea << std::endl;
	}

	fin.close();
	fout.close();


}

