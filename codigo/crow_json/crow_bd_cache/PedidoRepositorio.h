#pragma once

#include <soci/soci.h>
#include <optional>
#include <vector>

#include "Pedido.h"

class PedidoRepositorio
{
public:
    // Ahora recibe un shared_ptr
    PedidoRepositorio(std::shared_ptr<soci::session> sql)
        : sql_(sql)
    {
    }

    PedidoRepositorio(const PedidoRepositorio&) = delete;
    PedidoRepositorio& operator=(const PedidoRepositorio&) = delete;

    std::optional<Pedido> read(int id);
    bool create(const Pedido& p);
    bool update(const Pedido& p);
    bool delete_(int id);
    std::vector<Pedido> select();

private:
    // Ahora es un shared_ptr, no una referencia
    std::shared_ptr<soci::session> sql_;
};
