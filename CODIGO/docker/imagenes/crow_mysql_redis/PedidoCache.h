#pragma once

#include <optional>
#include <hiredis/hiredis.h>

#include "Pedido.h"

class PedidoCache {
public:
    PedidoCache();
    ~PedidoCache();

    std::optional<Pedido> getPedido(int id);
    void savePedido(Pedido p);

    PedidoCache(const PedidoCache&) = delete;
    PedidoCache& operator=(const PedidoCache&) = delete;

private:
    redisContext* contexto;
};


