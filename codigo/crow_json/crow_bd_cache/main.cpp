// crow_bd_cache.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Pedido.h"
#include "PedidoCache.h"
#include "PedidoRepositorio.h"
#include "PedidoService.h"
#include "PedidoCROW.h"

int main()
{
	// Crear la sesion con soci:
	soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

	// Crear el repositorio e inyectar la sesion de soci:
	PedidoRepositorio repositorio(sql);

	// Crear la cache:
	PedidoCache cache;

	// Crear el servicio (logica de negocio) e inyectar cache y repositorio
	PedidoService service(cache, repositorio);

	// Crear el servicio crow e inyectar service:
	PedidoCROW servicioCrow(service);
	servicioCrow.run();
}

