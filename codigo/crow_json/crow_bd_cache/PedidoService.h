#pragma once

#include "Pedido.h"
#include "PedidoCache.h"
#include "PedidoRepositorio.h"

#include <optional>
#include <vector>

class PedidoService
{
private:
	PedidoCache& cache;
	PedidoRepositorio& repositorio;

public:
	PedidoService(PedidoCache&, PedidoRepositorio&);
	std::optional<Pedido> read(int);
	std::vector<Pedido> selectAll();
	~PedidoService();
};

