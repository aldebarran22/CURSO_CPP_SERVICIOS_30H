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

    // Cerrar conexion:
    mysql_close(con);

}


int main()
{
    testMySQL();
    return 0;
}

