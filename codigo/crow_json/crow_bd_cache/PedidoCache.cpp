#include <string>
#include <nlohmann/json.hpp>

#include "Pedido.h"
#include "PedidoCache.h"

using json = nlohmann::json;

PedidoCache::PedidoCache()
{
	this->contexto = redisConnect("127.0.0.1", 6379);
	if (!this->contexto || this->contexto->err) {
		throw std::runtime_error("No se puede conectar con redis");
	}
}

/*
std::optional<Pedido> PedidoCache::getPedido(int id)
{
	std::string key = "pedido" + std::to_string(id);

	// Buscar la clave:
	redisReply* reply = (redisReply*)redisCommand(this->contexto, "GET %s", key.c_str());

	if (reply->type == REDIS_REPLY_STRING) {
		std::string cadJson = reply->str;
		json j = json::parse(cadJson);

		Pedido p = j.get<Pedido>();

		freeReplyObject(reply);
		return p;
	}

	freeReplyObject(reply);
	return std::nullopt;
}
*/

std::optional<Pedido> PedidoCache::getPedido(int id)
{
	std::string key = "pedido" + std::to_string(id);

	redisReply* reply = (redisReply*)redisCommand(this->contexto, "GET %s", key.c_str());

	if (!reply) {
		// La conexión puede haberse caído, marcamos el contexto en error
		// o lanzamos excepción para ver claramente el problema.
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
		catch (const std::exception& e) {
			// log si quieres
			// std::cerr << "Error parseando JSON desde Redis: " << e.what() << std::endl;
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
