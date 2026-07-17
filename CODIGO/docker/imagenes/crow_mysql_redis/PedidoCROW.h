#pragma once

#include "PedidoService.h"

class PedidoCROW
{
public:
    // Ahora recibe un shared_ptr
    PedidoCROW(std::shared_ptr<PedidoService> service)
        : service(service)
    {
    }

    PedidoCROW(const PedidoCROW&) = delete;
    PedidoCROW& operator=(const PedidoCROW&) = delete;

    void run();
    ~PedidoCROW() = default;

private:
    // Ahora es un shared_ptr, no una referencia
    std::shared_ptr<PedidoService> service;
};
