// redis.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <hiredis/hiredis.h>

int main()
{
    redisContext* context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        if (context) {
            std::cerr << "Error en la conexión: " << context->errstr << std::endl;
        }
        else {
            std::cerr << "No se pudo asignar el contexto" << std::endl;
        }

        return 1;
    }

    redisReply* reply = (redisReply*)redisCommand(context, "SET %s %s", "k8", "prueba");
    std::cout << "Respuesta: " << reply->str << std::endl;
    freeReplyObject(reply);

    reply = (redisReply*)redisCommand(context, "GET %s", "k8");
    std::cout << "Respuesta: " << reply->str << std::endl;
    freeReplyObject(reply);

    redisFree(context);
    return 0;
}

