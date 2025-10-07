#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Empleado
{
public:
	int id;
	std::string nombre;
	std::string cargo;

	Empleado();
	Empleado(int, std::string, std::string);
	nlohmann::json to_json() const;
	static Empleado from_json(const nlohmann::json& j);
	~Empleado();
};


