#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;


#include "EmpleadoCache.h"

EmpleadoCache::EmpleadoCache()
{
	this->contexto = redisConnect("127.0.0.1", 6379);
	if (!this->contexto || this->contexto->err) {
		throw std::runtime_error("Error al conectar con el servidor de Redis");
	}
}

std::optional<Empleado> EmpleadoCache::getEmpleado(int id)
{
	// Montamos la clave para buscar en Redis:
	std::string key = "empleado" + std::to_string(id);

	// Buscar la clave:
	redisReply* reply = (redisReply*)redisCommand(this->contexto, "GET %s", key.c_str());

	// REcuperamos el contenido de la clave:
	if (reply->type == REDIS_REPLY_STRING) {

		// Devolver el empleado
		std::string cadJson = reply->str;
		//std::cout << "getEmpleado: " << cadJson << std::endl;

		json j = json::parse(cadJson);
	
		// Para convertirlo a objeto:
		Empleado emp = j.get<Empleado>();

		freeReplyObject(reply);
		return emp;
	}

	freeReplyObject(reply);
	return std::nullopt;
}

void EmpleadoCache::saveEmpleado(Empleado emp)
{
	// Montamos la clave para buscar en Redis:
	std::string key = "empleado" + std::to_string(emp.id);

	json j = emp;
	std::string strEmp = j.dump();
	//std::cout << "saveEmpleado: " << emp.to_string() << " " << strEmp << std::endl;

	// Guardamos el objeto empleado como una cadena en la clave:
	redisReply* reply = (redisReply*)redisCommand(this->contexto, "SET %s %s", key.c_str(), strEmp.c_str());
	freeReplyObject(reply);
}

EmpleadoCache::~EmpleadoCache()
{
	if (this->contexto) {
		redisFree(this->contexto);
	}
}
