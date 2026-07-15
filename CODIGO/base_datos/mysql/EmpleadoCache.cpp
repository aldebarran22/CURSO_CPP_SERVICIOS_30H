#include <stdexcept>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

#include "EmpleadoCache.h"

EmpleadoCache::EmpleadoCache()
{
	std::string mensaje = "";

	this->contexto = redisConnect("127.0.0.1", 6379);
	if (this->contexto == nullptr || this->contexto->err) {
		if (this->contexto) {
			mensaje = this->contexto->errstr;
		}
		throw std::runtime_error("Error al conectar con redis "+mensaje);
	}
}

std::optional<Empleado> EmpleadoCache::getEmpleado(int id)
{
	std::string key = "empleado" + std::to_string(id);

	// Buscar la clave:
	redisReply* reply = (redisReply*)redisCommand(this->contexto, "GET %s", key.c_str());

	if (reply->type == REDIS_REPLY_STRING) {
		// La hemos encontrado:
		std::string cadjson = reply->str;
		json j = json::parse(cadjson);

		Empleado e = j.get<Empleado>();
		std::cout << "Recupera " << id << " de la cache" << std::endl;

		freeReplyObject(reply);
		return e;
	}
	else {
		freeReplyObject(reply);
		return std::nullopt;
	}
}

void EmpleadoCache::saveEmpleado(const Empleado& e)
{
}

EmpleadoCache::~EmpleadoCache()
{
	if (this->contexto) {
		redisFree(this->contexto);
		this->contexto = nullptr;
	}
}
