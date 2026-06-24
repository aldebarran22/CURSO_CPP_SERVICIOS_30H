// mysql.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <optional>
#include <vector>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

#include "Empleado.h"
#include "EmpleadoRepositorio.h"

int main()
{
    soci::session sql(soci::mysql, "db=empresa3 user=antonio password=antonio host=127.0.0.1 port=3307");
    EmpleadoRepositorio repo(sql);

    std::optional<Empleado> emp = repo.read(1);
    if (emp) {
        std::cout << emp->nombre << " " << emp->cargo << std::endl;
    }
    else {
        std::cout << "No existe el empleado" << std::endl;
    }

    std::vector<Empleado> empleados = repo.select();
    for (const auto& e : empleados) {
        std::cout << e.nombre << " " << e.cargo << std::endl;
    }

}

