// csvjson.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Pedido.h"

int main()
{
	std::string pathIn = "..\\..\\..\\practicas\\ficheros\\pedidos_final.csv";
	std::string pathOut = "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json";

	std::ifstream fin(pathIn);
	std::ofstream fout(pathOut);
	std::vector<nlohmann::json> array; // Almacenar los docs de json (1 por pedido)
	nlohmann::json doc; // Documento final de json, convierte automaticamente el vector -> array json
	bool cabs = true;

	std::string linea;

	if (!fin) {
		std::cerr << "Fichero no encontrado: " << pathIn << std::endl;
		return 1;
	}

	while (std::getline(fin, linea)) {
		//std::cout << linea << std::endl;

		if (cabs) {
			cabs = false;
		}
		else {
			Pedido p(linea);
			// Convertir el pedido a json:
			array.push_back(p.to_json());
		}
	}

	// Convertir el vector en un array:
	doc = array;

	// A la consola:
	std::cout << doc.dump(4) << std::endl;

	// Al fichero json:
	fout << doc.dump(4);

	fin.close();
	fout.close();

	return 0;
}
