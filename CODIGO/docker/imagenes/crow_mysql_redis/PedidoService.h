#pragma once

#include "Pedido.h"
#include "PedidoCache.h"
#include "PedidoRepositorio.h"

#include <optional>
#include <vector>

class PedidoService
{
private:
    std::shared_ptr<PedidoCache> cache;
    std::shared_ptr<PedidoRepositorio> repositorio;

public:
    PedidoService(std::shared_ptr<PedidoCache> cache,
        std::shared_ptr<PedidoRepositorio> repositorio)
        : cache(cache), repositorio(repositorio)
    {
    }

    PedidoService(const PedidoService&) = delete;
    PedidoService& operator=(const PedidoService&) = delete;

    std::optional<Pedido> read(int);
    std::vector<Pedido> selectAll();
    ~PedidoService() = default;
};
