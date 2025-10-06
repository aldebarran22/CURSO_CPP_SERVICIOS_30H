#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Pedido
{
public:
	std::string idpedido;
	std::string cliente;
	std::string empresa;
	std::string empleado;
	float importe;
	std::string pais;

	Pedido();
	Pedido(const std::string, char = ';');
	nlohmann::json to_json() const;
	static Pedido from_json(const nlohmann::json& j);
	~Pedido();
};

