#pragma once
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
	Pedido(std::string, char = ';');
	

	~Pedido();
};

inline void to_json(json& j, const Pedido& p) {
	j = json{
		{"idpedido", p.idpedido},
		{"cliente", p.cliente },
		{ "empleado", p.empleado },
		{ "empresa", p.empresa },
		{ "importe", p.importe },
		{ "pais", p.pais }
	};
}
inline void from_json(const nlohmann::json& j, Pedido& p) {
	j.at("idpedido").get_to(p.idpedido);
	j.at("cliente").get_to(p.cliente);
	j.at("empleado").get_to(p.empleado);
	j.at("empresa").get_to(p.empresa);
	j.at("importe").get_to(p.importe);
	j.at("pais").get_to(p.pais);
}

