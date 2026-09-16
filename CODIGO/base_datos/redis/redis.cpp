// redis.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <hiredis/hiredis.h>


void testRedis() {
    redisContext* context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {

        if (context) {
            std::cout << context->errstr << std::endl;
        }
        else {
            std::cout << "No se ha podido crear el contexto";
        }

        return;
    }

    redisReply* reply = (redisReply*)redisCommand(context, "GET k1");
    std::cout << reply->str << std::endl;
    freeReplyObject(reply);

    redisFree(context);
}

int main()
{
    testRedis();
}

