#include "EmpleadoCache.h"

EmpleadoCache::EmpleadoCache()
{
	this->contexto = redisConnect("127.0.0.1", 6379);
	if (!this->contexto || this->contexto->err) {
		throw std::runtime_error("Error al conectar con Redis");
	}
}

std::optional<Empleado> EmpleadoCache::getEmpleado(int id)
{
	std::string key = "empleado:" + std::to_string(id);

	// Buscar la clave en redis:
	redisReply* reply = (redisReply*)redisCommand(this->contexto, "GET %s", key);
	if (reply->type == REDIS_REPLY_STRING) {
		Empleado emp = Empleado::deserialize(reply->str);
		return emp;
	}

	return std::optional<Empleado>();
}

void EmpleadoCache::saveEmpleado(Empleado emp)
{
	std::string key = "empleado:" + std::to_string(emp.id);
	redisReply* reply = (redisReply*)redisCommand(this->contexto, "SET %s %s", key.c_str(), emp.serialize().c_str());
	freeReplyObject(reply);
}

EmpleadoCache::~EmpleadoCache()
{
	if (this->contexto)
		redisFree(this->contexto);
}
