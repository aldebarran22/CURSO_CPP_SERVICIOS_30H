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
	std::string pathIn = "";
	std::string pathOut = "";

	std::ifstream fin(pathIn);
	std::ofstream fin(pathOut);

	std::vector<nlohmann::json> array;
	nlohmann::json doc;


}

