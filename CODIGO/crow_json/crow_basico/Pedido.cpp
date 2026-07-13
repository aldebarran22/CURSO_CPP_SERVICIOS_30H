#include <vector>

#include "Pedido.h"
#include "utilidades.h"

Pedido::Pedido() {}

Pedido::Pedido(std::string linea, char sep)
{
	std::vector<std::string> campos;

	Utilidades::split(linea, sep, campos);

	this->idpedido = campos.at(0);
	this->cliente = campos.at(1);
	this->empresa = campos.at(2);
	this->empleado = campos.at(3);
	this->importe = std::stof(campos.at(4));
	this->pais = campos.at(5);
}


Pedido::~Pedido()
{
}

