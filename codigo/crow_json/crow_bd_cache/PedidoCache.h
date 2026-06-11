#pragma once

#include <optional>
#include <hiredis/hiredis.h>

#include "Pedido.h"

class PedidoCache
{
private:
	redisContext* contexto;

public:
	PedidoCache();
	std::optional<Pedido> getPedido(int id);
	void savePedido(Pedido p);
	~PedidoCache();
};

