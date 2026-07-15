// redis.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <hiredis/hiredis.h>

int main()
{
	redisContext* context = redisConnect("127.0.0.1", 6379);
	if (context == nullptr || context->err) {

		if (context) {
			std::cerr << "Error en la conexion: " << context->errstr << std::endl;
		}
		else {
			std::cerr << "No se pudo asignar el contexto" << std::endl;
		}

		return 1;
	}


}

