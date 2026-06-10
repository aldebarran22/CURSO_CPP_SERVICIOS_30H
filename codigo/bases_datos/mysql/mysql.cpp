// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <optional>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Pedido.h"
#include <vector>

#include "PedidoRepositorio.h"


int main()
{
	try {
		soci::session sql(soci::mysql, "db=empresa3 user=root password=antonio host=127.0.0.1 port=3307");
		PedidoRepositorio repo(sql);

		int id = 99;
		auto pedido = repo.read(id);

		if (pedido) {
			std::cout << pedido->idpedido << " " << pedido->cliente << " " << pedido->importe << std::endl;
		}
		else {
			std::cout << "No exite el pedido: " << id << std::endl;
		}

		std::vector<Pedido> pedidos = repo.select();
		for (const auto& p : pedidos) {
			std::cout << p.idpedido << " " << p.cliente << " " << p.importe << std::endl;
		}

	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
   }
}
