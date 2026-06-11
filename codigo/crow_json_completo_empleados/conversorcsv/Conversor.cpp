#include "Conversor.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

#include "Pedido.h"
#include "Utils.h"

void Conversor::conversorCSVToJson(const std::string& path, const std::string& pathJson)
{
	std::ifstream fin(path);
	std::ofstream fout(pathJson);

	std::string linea;
	std::vector<std::string> campos;
	bool cabs = true;
	std::vector<nlohmann::json> array;
	nlohmann::json grupo;

	if (!fin) {
		std::cerr << "No se ha encontrado el fichero: " << path << std::endl;
		return;
	}

	while (std::getline(fin, linea)) {
		std::cout << linea << std::endl;

		if (cabs) {
			cabs = false;
		}
		else {
			Pedido p(linea);
			array.push_back(p.to_json());
		}
	}
	fin.close();
	grupo = array;

	std::cout << grupo.dump(4) << std::endl;
	fout << grupo.dump(4);
	fout.close();
}
