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

	e.id = j.at("id").get<std::string>();
	e.nombre = j.at("nombre").get<std::string>();
	e.cargo = j.at("cargo").get<std::string>();
	return e;
}

Empleado::~Empleado()
{
}