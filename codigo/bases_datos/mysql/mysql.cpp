// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <optional>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Pedido.h"
#include "Empleado.h"
#include <vector>

#include "PedidoRepositorio.h"
#include "EmpleadoRepositorio.h"


void test2Repo() {
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");

    EmpleadoRepository repo(sql);

    try {
        // Eliminar
        repo.eliminar(10);

        // Insertar
        repo.insertar({ 10, "Laura", "Directivo" });

        // Obtener
        int id = 10;
        auto e = repo.recuperarEmpleado(id);
        if (e) {
            std::cout << e->nombre << " - " << e->cargo << std::endl;
        }
        else {
            std::cout << "No se encuentra el empleado con id: " << id << std::endl;
        }

        // Listar
        for (const auto& emp : repo.listarTodos()) {
            std::cout << emp.id << ": " << emp.nombre << " (" << emp.cargo << ")\n";
        }

        // Actualizar
        if (e) {
            e->cargo = "Directora Creativa";
            repo.actualizar(*e);
        }

    }
    catch (std::exception& e) {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
}


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
