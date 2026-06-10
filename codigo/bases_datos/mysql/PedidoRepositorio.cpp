#include "PedidoRepositorio.h"

PedidoRepositorio::PedidoRepositorio(soci::session& sql):sql_(sql)
{
}

std::optional<Pedido> PedidoRepositorio::read(int id)
{
	return std::optional<Pedido>();
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
