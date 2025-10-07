// base_datos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <mysql/mysql.h>


#define SERVER "localhost"
#define USR "antonio"
#define PASS "antonio"
#define BD "empresa3"
#define PORT 3307


void testMySQL() {
    MYSQL* con;
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[1];
    int param_id = 1;

    // Inicializar la conexion:
    con = mysql_init(nullptr);

    if (!mysql_real_connect(con, SERVER, USR, PASS, BD, PORT, nullptr, 0)) {
        std::cerr << "Error al conectar" << std::endl;
        return;
    }

    // Crear la sentencia:
    const char* sql = "select nombre from empleados where id=?";
    stmt = mysql_stmt_init(con);
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        std::cerr << "Error en la sentencia: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Vincular parámetro
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char*)&param_id;
    bind[0].is_null = 0;
    bind[0].length = 0;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Error en el bind del parametro: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Ejecutar la consulta:
    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Error al ejecutar la query: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Obtener resultados
    MYSQL_BIND result[1];
    char nombre[100];
    unsigned long nombre_length;
    memset(result, 0, sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_STRING;
    result[0].buffer = nombre;
    result[0].buffer_length = sizeof(nombre);
    result[0].length = &nombre_length;

    mysql_stmt_bind_result(stmt, result);
    while (mysql_stmt_fetch(stmt) == 0) {
        std::cout << "nombre: " << std::string(nombre, nombre_length) << std::endl;
    }

    mysql_stmt_close(stmt);

    // Cerrar conexion:
    mysql_close(con);

}

void testRecuperarConsulta() {
    MYSQL* con;
    MYSQL_RES* res;
    MYSQL_ROW row;

    // Conexión
    con = mysql_init(nullptr);
    if (!mysql_real_connect(con, SERVER, USR, PASS, BD, PORT, nullptr, 0)) {
        std::cerr << "Error de conexión: " << mysql_error(con) << std::endl;
        return;
    }

    // Consulta directa sin parámetros
    const char* query = "SELECT id, nombre, cargo FROM empleados";
    if (mysql_query(con, query)) {
        std::cerr << "Error en la consulta: " << mysql_error(con) << std::endl;
        mysql_close(con);
        return;
    }

    // Obtener resultados
    res = mysql_store_result(con);
    if (!res) {
        std::cerr << "Error al obtener resultados: " << mysql_error(con) << std::endl;
        mysql_close(con);
        return;
    }

    // Mostrar resultados
    std::cout << "ID;Nombre;Cargo\n";
    while ((row = mysql_fetch_row(res))) {
        std::cout << row[0] << ";" << row[1] << ";" << row[2] << "\n";
    }

    // Limpieza
    mysql_free_result(res);
    mysql_close(con);
}

void testInsertar() {
    MYSQL* con;
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[3];

    // Datos a insertar
    int id = 10;
    const char* nombre = "Laura Gómez";
    const char* cargo = "Analista";

    // Conexión
    con = mysql_init(nullptr);
    if (!mysql_real_connect(con, SERVER, USR, PASS, BD, PORT, nullptr, 0)) {
        std::cerr << "Error de conexión: " << mysql_error(con) << std::endl;
        return;
    }

    // Preparar sentencia
    const char* query = "INSERT INTO empleados (id, nombre, cargo) VALUES (?, ?, ?)";
    stmt = mysql_stmt_init(con);
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Error al preparar la sentencia: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Vincular parámetros
    memset(bind, 0, sizeof(bind));

    // id
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = (char*)&id;
    bind[0].is_null = 0;
    bind[0].length = 0;

    // nombre
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char*)nombre;
    bind[1].buffer_length = strlen(nombre);
    bind[1].is_null = 0;
    bind[1].length = 0;

    // cargo
    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char*)cargo;
    bind[2].buffer_length = strlen(cargo);
    bind[2].is_null = 0;
    bind[2].length = 0;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Error al vincular parámetros: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    // Ejecutar
    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Error al ejecutar la sentencia: " << mysql_stmt_error(stmt) << std::endl;
        return;
    }

    std::cout << "Fila insertada correctamente." << std::endl;

    // Limpieza
    mysql_stmt_close(stmt);
    mysql_close(con);
}

void testTransacciones() {
    MYSQL* con = mysql_init(nullptr);
    if (!mysql_real_connect(con, SERVER, USR, PASS, BD, PORT, nullptr, 0)) {
        std::cerr << "Error de conexión: " << mysql_error(con) << std::endl;
        return;
    }

    // Desactivar autocommit para iniciar transacción
    mysql_autocommit(con, 0);

    // Ejecutar varias operaciones
    if (mysql_query(con, "INSERT INTO empleados (id, nombre, cargo) VALUES (201, 'Ana', 'Disenyadora')") ||
        mysql_query(con, "INSERT INTO empleados (id, nombre, cargo) VALUES (202, 'Luis', 'Contador')")) {
        std::cerr << "Error en la transacción: " << mysql_error(con) << std::endl;
        mysql_rollback(con);  // Revertir si hay error
    }
    else {
        mysql_commit(con);    // Confirmar si todo salió bien
        std::cout << "Transacción completada correctamente." << std::endl;
    }

    mysql_close(con);
}

int main()
{   
    //testMySQL();
    //testRecuperarConsulta();
    //testInsertar();
    testTransacciones();
    return 0;
}
