#include <string>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <iostream>

#include "Pedido.h"
#include "PedidoCache.h"

using json = nlohmann::json;

PedidoCache::PedidoCache()
{
    // Leer variables de entorno (Docker)
    const char* envHost = std::getenv("REDIS_HOST");
    const char* envPort = std::getenv("REDIS_PORT");

    // Valores por defecto (Visual Studio)
    std::string host = envHost ? envHost : "127.0.0.1";
    int port = envPort ? std::stoi(envPort) : 6379;

    std::cout << "Conectando a Redis en " << host << ":" << port << std::endl;

    this->contexto = redisConnect(host.c_str(), port);

    if (!this->contexto || this->contexto->err) {
        std::string err = this->contexto ? this->contexto->errstr : "No se pudo crear contexto Redis";
        throw std::runtime_error("No se puede conectar con redis: " + err);
    }
}

std::optional<Pedido> PedidoCache::getPedido(int id)
{
    std::string key = "pedido" + std::to_string(id);

    redisReply* reply = (redisReply*)redisCommand(this->contexto, "GET %s", key.c_str());

    if (!reply) {
        throw std::runtime_error("redisCommand devolvió nullptr (posible desconexión de Redis)");
    }

    std::optional<Pedido> resultado;

    if (reply->type == REDIS_REPLY_STRING) {
        try {
            std::string cadJson = reply->str;
            json j = json::parse(cadJson);
            Pedido p = j.get<Pedido>();
            resultado = p;
        }
        catch (...) {
            // Error parseando JSON ? ignoramos
        }
    }

    freeReplyObject(reply);
    return resultado;
}

void PedidoCache::savePedido(Pedido p)
{
    std::string key = "pedido" + std::to_string(p.idpedido);

    json j = p;
    std::string strPedido = j.dump();

    redisReply* reply = (redisReply*)redisCommand(this->contexto, "SET %s %s", key.c_str(), strPedido.c_str());
    freeReplyObject(reply);
}

PedidoCache::~PedidoCache()
{
    if (this->contexto) {
        redisFree(this->contexto);
    }
}
