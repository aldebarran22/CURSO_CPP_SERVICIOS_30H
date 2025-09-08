#include <vector>

#include "Pedido.h"
#include "CSVJson.h"
#include "utilidades.h"

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

nlohmann::json Pedido::to_json() const
{
	return nlohmann::json{ {"idpedido", this->idpedido},
							{"cliente", this->cliente},
							{"empresa", this->empresa},
							{"empleado", this->empleado},
							{"importe", this->importe},
							{"pais", this->pais}};
}

xmlNodePtr Pedido::to_xml() const 
{
	xmlNodePtr nodo = xmlNewNode(nullptr, BAD_CAST "pedido");

	xmlNewChild(nodo, nullptr, BAD_CAST "idpedido", BAD_CAST this->idpedido.c_str());
	xmlNewChild(nodo, nullptr, BAD_CAST "cliente", BAD_CAST this->cliente.c_str());
	xmlNewChild(nodo, nullptr, BAD_CAST "empresa", BAD_CAST this->empresa.c_str());
	xmlNewChild(nodo, nullptr, BAD_CAST "empleado", BAD_CAST this->empleado.c_str());
	xmlNewChild(nodo, nullptr, BAD_CAST "empleado", BAD_CAST std::to_string(this->importe).c_str());
	xmlNewChild(nodo, nullptr, BAD_CAST "pais", BAD_CAST this->pais.c_str());

	return nodo;
}

Pedido::~Pedido()
{
}
