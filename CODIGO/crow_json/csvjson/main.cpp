// csvjson.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

int main()
{
	std::string pathIn = "..\\..\\..\\practicas\\ficheros\\pedidos_final.csv";
	std::string pathOut = "..\\..\\..\\practicas\\ficheros\\out\\pedidos.json";

	std::ifstream fin(pathIn);
	std::ofstream fout(pathOut);

	std::string linea;

	if (!fin) {
		std::cerr << "Fichero no encontrado: " << pathIn << std::endl;
		return 1;
	}

	while (std::getline(fin, linea)) {
		std::cout << linea << std::endl;
	}

	fin.close();
	fout.close();

	return 0;
}
