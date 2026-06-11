// crow_bd_cache.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <optional>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Pedido.h"
#include "PedidoCache.h"
#include "PedidoRepositorio.h"
#include "PedidoService.h"
#include "PedidoCROW.h"


int main()
{
    try {
        // Crear la sesión con soci (en heap, gestionada por shared_ptr)
        auto sql = std::make_shared<soci::session>(
            soci::mysql,
            "db=empresa3 user=root password=antonio host=127.0.0.1 port=3307"
        );

        // Crear el repositorio e inyectar la sesión
        auto repositorio = std::make_shared<PedidoRepositorio>(sql);

        // Crear la cache
        auto cache = std::make_shared<PedidoCache>();

        // Crear el servicio (lógica de negocio)
        auto service = std::make_shared<PedidoService>(cache, repositorio);

        // Crear el servicio Crow e inyectar service
        PedidoCROW servicioCrow(service);
        servicioCrow.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
}
