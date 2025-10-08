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
	Empleado(int, const std::string&, const std::string&);
	nlohmann::json to_json() const;
	static Empleado from_json(const nlohmann::json& j);
	std::string serialize() const;
	static Empleado deserialize(const std::string& data);
	~Empleado();
};


