#pragma once

#include <string>
#include <nlohmann/json.hpp>


class Pedido
{	

public:
	int idpedido;
	std::string cliente;
	std::string empresa;
	std::string empleado;
	double importe;
	std::string pais;

	Pedido();
	Pedido(std::string, char =';');
	nlohmann::json to_json() const;
	static Pedido from_json(const nlohmann::json& j);
	
	~Pedido();
};

