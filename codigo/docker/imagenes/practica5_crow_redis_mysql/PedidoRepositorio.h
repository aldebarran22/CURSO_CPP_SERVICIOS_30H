#pragma once

#include <mysql/mysql.h>
#include <optional>
#include <vector>
#include <memory>

#include "Pedido.h"

class PedidoRepositorio
{
public:
    PedidoRepositorio(MYSQL* conn)
        : conn_(conn)
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
    MYSQL* conn_;
};
