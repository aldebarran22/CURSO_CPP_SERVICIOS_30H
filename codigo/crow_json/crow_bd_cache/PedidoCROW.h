#pragma once

#include "PedidoService.h"

class PedidoCROW
{
	PedidoCROW(PedidoService&);
	void run();
	~PedidoCROW();

private:
	PedidoService& service;
};

