#pragma once

#include "PedidoService.h"

class PedidoCROW
{
public:
	PedidoCROW(PedidoService&);
	void run();
	~PedidoCROW();

private:
	PedidoService& service;
};

