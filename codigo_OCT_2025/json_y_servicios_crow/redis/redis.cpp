// redis.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <hiredis/hiredis.h>


int main()
{
   // Conectar con el servidor de redis:
	redisContext* con = redisConnect("127.0.0.1", 6379);
	if (con == nullptr || con->err) {
		if (con) {
			std::cerr << "Error en la conexion: " << con->errstr << std::endl;
		}
		else {
			std::cerr << "No se pudo asignar el contexto de redis" << std::endl;
		}
		return 1;
	}

	// Ejecutar comandos dentro de redis:
	redisReply* reply = (redisReply*)redisCommand(con, "set clave valor");
	std::cout << "Respuesta: " << reply->str << std::endl;
	freeReplyObject(reply);

	reply = (redisReply*)redisCommand(con, "get clave");
	std::cout << "Respuesta: " << reply->str << std::endl;
	freeReplyObject(reply);

	redisFree(con);
	return 0;
}

