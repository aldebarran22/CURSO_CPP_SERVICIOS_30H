#include <string>

#include "PedidoRepositorio.h"
#include "PedidoService.h"

std::optional<Pedido> PedidoRepositorio::read(int id)
{
    std::string query =
        "SELECT p.idpedido, p.idcliente, e.nombre AS empleado, "
        "emp.nombre AS empresa, p.importe, p.pais "
        "FROM pedidos p "
        "INNER JOIN empresasenvios emp ON p.idempresaenvio = emp.id "
        "INNER JOIN empleados e ON p.idempleado = e.id "
        "WHERE idpedido = " + std::to_string(id);

    if (mysql_query(conn_, query.c_str()) != 0)
        return std::nullopt;

    MYSQL_RES* res = mysql_store_result(conn_);
    if (!res)
        return std::nullopt;

    MYSQL_ROW row = mysql_fetch_row(res);
    if (!row) {
        mysql_free_result(res);
        return std::nullopt;
    }

    Pedido p;
    p.idpedido = std::stoi(row[0]);
    p.cliente  = row[1];
    p.empleado = row[2];
    p.empresa  = row[3];
    p.importe  = std::stod(row[4]);
    p.pais     = row[5];

    mysql_free_result(res);
    return p;
}


bool PedidoRepositorio::create(const Pedido& p)
{
	return false;
}

bool PedidoRepositorio::update(const Pedido& p)
{
	return false;
}

bool PedidoRepositorio::delete_(int id)
{
	return false;
}

std::vector<Pedido> PedidoRepositorio::select()
{
    std::vector<Pedido> pedidos;

    std::string query =
        "SELECT p.idpedido, p.idcliente, e.nombre AS empleado, "
        "emp.nombre AS empresa, p.importe, p.pais "
        "FROM pedidos p "
        "INNER JOIN empresasenvios emp ON p.idempresaenvio = emp.id "
        "INNER JOIN empleados e ON p.idempleado = e.id";

    if (mysql_query(conn_, query.c_str()) != 0)
        return pedidos;

    MYSQL_RES* res = mysql_store_result(conn_);
    if (!res)
        return pedidos;

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res))) {
        Pedido p;
        p.idpedido = std::stoi(row[0]);
        p.cliente  = row[1];
        p.empleado = row[2];
        p.empresa  = row[3];
        p.importe  = std::stod(row[4]);
        p.pais     = row[5];
        pedidos.push_back(p);
    }

    mysql_free_result(res);
    return pedidos;
}
