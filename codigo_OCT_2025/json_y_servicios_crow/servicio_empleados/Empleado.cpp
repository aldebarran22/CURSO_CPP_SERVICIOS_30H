#include "Empleado.h"

Empleado::Empleado()
{
}

Empleado::Empleado(int id, const std::string& nombre, const std::string& cargo):id(id), nombre(nombre), cargo(cargo)
{
}

nlohmann::json Empleado::to_json() const {
	return nlohmann::json{ {"id", this->id},
							{"nombre", this->nombre},
							{"cargo", this->cargo} };
}

Empleado Empleado::from_json(const nlohmann::json& j) {
	Empleado e;

	e.id = j.at("id").get<int>();
	e.nombre = j.at("nombre").get<std::string>();
	e.cargo = j.at("cargo").get<std::string>();
	return e;
}

std::string Empleado::serialize() const
{
	return std::to_string(id) + "|" + nombre + "|" + cargo;
}

Empleado Empleado::deserialize(const std::string& data)
{
	int p1 = data.find("|");
	int p2 = data.find("|", p1+1);

	Empleado e;
	e.id = std::stoi(data.substr(0, p1));
	e.nombre = data.substr(p1 + 1, p2 - p1 - 1);
	e.cargo = data.substr(p2 + 1);
	return e;
}

Empleado::~Empleado()
{
}