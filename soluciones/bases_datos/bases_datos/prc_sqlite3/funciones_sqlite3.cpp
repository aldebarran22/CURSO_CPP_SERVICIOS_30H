#include "funciones_sqlite3.h"
#include "Empleado.h"
#include "IEmpleadoDAO.h"
#include "EmpleadoDAO.h"

#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <vector>

int testSqlite3() {
    sqlite3* db;
    char* errMsg = nullptr;

    // Abrir o crear la BD:
    int rc = sqlite3_open("bd_sqlite3.db", &db);
    if (rc) {
        std::cerr << "Error al crear / abrir la BD" << std::endl;
        return rc;
    }

    // Crear una tabla:
    const char* sql = "create table if not exists usuarios(id integer, nombre text, primary key ('id' autoincrement));";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "No se ha podido crear la tabla " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Insertar datos
    const char* sql_i = "insert into usuarios(nombre) values('Admin');";
    rc = sqlite3_exec(db, sql_i, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "No se ha podido crear una fila " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    // Consultar datos:
    const char* sql_s = "select id, nombre from usuarios;";
    rc = sqlite3_exec(db, sql_s, [](void*, int argc, char** argv, char** colNames) -> int {
        for (int i = 0; i < argc; i++) {
            std::cout << colNames[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
        }
        std::cout << "--------------------" << std::endl;
        return 0;

        }, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error al consultar datos: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    if (db != nullptr) {
        sqlite3_close(db);
    }

    return 0;
}

void testEmpleado() {
    Empleado emp(1, "Davolio", "Representante de ventas");
    std::cout << "Empleado: " << emp.to_string() << std::endl;
}

void testEmpleadoDAO(){
    IEmpleadoDAO* dao;
    std::vector<Empleado> empleados;
    Empleado emp;

    try {
        dao = new EmpleadoDAO("empresa3.db");
        empleados = dao->selectAll();
        std::cout << "Listado de empleados:" << std::endl;
        for (Empleado e : empleados) {
            std::cout << e.to_string() << std::endl;
        }
        std::cout << std::endl;

        std::cout << "Recuperar un empleado: " << std::endl;
        emp = dao->read(1);
        std::cout << emp.to_string() << std::endl;

        // Prueba de insertar:
        Empleado emp2(0, "Roberts", "Representante de Ventas");
        if (dao->create(&emp2)) {
            std::cout << "Fila insertada correctamente: " << emp2.to_string() << std::endl;
        }

        // Prueba de borrado:
        if (dao->del(21)) {
            std::cout << "fila eliminada correctamente " << std::endl;

        } else {
            std::cout << "No se ha podido eliminar la fila " << std::endl;
        }

        // Cargamos un registro, lo modificamos y lo actualizamos:
        std::cout << "Recuperar un empleado: " << std::endl;
        emp = dao->read(22);
        std::cout << emp.to_string() << std::endl;

        emp.setNombre("Miguel Sanz");
        emp.setCargo("Director");
        std::cout << " modificado: " << emp.to_string() << std::endl;
        if (dao->update(emp)) {
            std::cout << "fila actualizada correctamente " << std::endl;

        } else {
            std::cout << "No se ha podido actualizar la fila " << std::endl;       
        }

        delete dao;
    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}
