#include <string>

#include "PedidoRepositorio.h"
#include "PedidoService.h"

PedidoRepositorio::PedidoRepositorio(soci::session& sql):sql_(sql)
{
}

std::optional<Pedido> PedidoRepositorio::read(int id)
{
	Pedido p;
	soci::indicator ind;

	std::string sql = std::string("select p.idpedido, p.idcliente, e.nombre as empleado, ") +
		std::string("emp.nombre as empresa, p.importe, p.pais from pedidos p inner join empresasenvios emp ") +
		std::string("on p.idempresaenvio = emp.id inner join empleados e on p.idempleado = e.id where idpedido = :id");
	sql_ << sql, soci::use(id), soci::into(p.idpedido, ind), soci::into(p.cliente), soci::into(p.empresa),
		soci::into(p.empleado), soci::into(p.importe), soci::into(p.pais);

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
	std::vector<Pedido> pedidos;

	std::string sql = std::string("select p.idpedido, p.idcliente, e.nombre as empleado, ") +
		std::string("emp.nombre as empresa, p.importe, p.pais from pedidos p inner join empresasenvios emp ") +
		std::string("on p.idempresaenvio = emp.id inner join empleados e on p.idempleado = e.id");

	soci::rowset<soci::row> rs = sql_.prepare << sql;

	for (const auto& r : rs) {
		Pedido p;

		p.idpedido = r.get<int>(0);
		p.cliente = r.get<std::string>(1);
		p.empleado = r.get<std::string>(2);
		p.empresa = r.get<std::string>(3);
		p.importe = r.get<double>(4);
		p.pais = r.get<std::string>(5);

		pedidos.push_back(p);
	}

	return pedidos;
}
