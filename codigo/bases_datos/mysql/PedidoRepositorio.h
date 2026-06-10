#pragma once

#include <soci/soci.h>
#include <optional>
#include <vector>

#include "Pedido.h"

class PedidoRepositorio
{
public: 
	PedidoRepositorio(soci::session& sql);
	std::optional<Pedido> read(int id);
	bool create(const Pedido& p);
	bool update(const Pedido& p);
	bool delete_(int id);
	std::vector<Pedido> select();

private:
	soci::session& sql_;
};

