#include <string>

#include "PedidoRepositorio.h"

PedidoRepositorio::PedidoRepositorio(soci::session& sql):sql_(sql)
{
}

std::optional<Pedido> PedidoRepositorio::read(int id)
{
	Pedido p;
	soci::indicator ind;

	std::string sql = std::string("select p.idpedido, p.idcliente, e.nombre as empleado, ") +
		std::string("emp.nombre as empresa, p.pais from pedidos p inner join empresasenvios emp ") +
		std::string("on p.idempresaenvio = emp.id inner join empleados e on p.idempleado = e.id where idpedido = :id");
	sql_ << sql, soci::use(id), soci::into(p.idpedido, ind), soci::into(p.cliente), soci::into(p.empresa),
		soci::into(p.empleado), soci::into(p.pais);

	if (ind == soci::i_null) {
		return std::nullopt;
	}

	return p;
}

bool PedidoRepositorio::create(const Pedido& p)
{
	return false;
}

bool PedidoRepositorio::update(const Pedido& p)
{
	return false;
}

bool PedidoRepositorio::delete_(int id)
{
	return false;
}

std::vector<Pedido> PedidoRepositorio::select()
{
	return std::vector<Pedido>();
}
