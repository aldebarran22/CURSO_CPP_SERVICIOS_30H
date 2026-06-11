#include "PedidoService.h"

PedidoService::PedidoService(PedidoCache& cache, PedidoRepositorio& repositorio):cache(cache), repositorio(repositorio)
{

}

std::optional<Pedido> PedidoService::read(int id)
{
	// 1) Buscar en la cache:
	auto p = this->cache.getPedido(id);

	if (!p) {
		// Si no está en la cache:
		p = this->repositorio.read(id);

		if (p) {
			// Si esta en el repositorio se guarda en la cache:
			this->cache.savePedido(*p);
		}
	}

	return p;
}

std::vector<Pedido> PedidoService::selectAll()
{
	return this->repositorio.select();
}

PedidoService::~PedidoService()
{
}
