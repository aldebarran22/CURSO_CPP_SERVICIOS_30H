#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Pedido
{
public:
	std::string idpedido;	
	float importe;
	std::string empresa;
	std::string empleado;
	std::string cliente;
	std::string pais;

	Pedido();
	Pedido(const std::string, char = ';');
	nlohmann::json to_json() const;
	static Pedido from_json(const nlohmann::json& j);
	~Pedido();
};

