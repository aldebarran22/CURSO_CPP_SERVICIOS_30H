#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <libxml/tree.h>


class Pedido
{
	std::string idpedido;
	std::string cliente;
	std::string empresa;
	std::string empleado;
	float importe;
	std::string pais;

public:
	Pedido(std::string, char =';');
	nlohmann::json to_json() const;
	xmlNodePtr to_xml() const;
	~Pedido();
};

