#include <iostream>
#include <hiredis/hiredis.h>

int main() {
    // Conexión al servidor Redis en localhost:6379
    redisContext* context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        if (context) {
            std::cerr << "Error de conexión: " << context->errstr << std::endl;
        }
        else {
            std::cerr << "No se pudo asignar contexto Redis" << std::endl;
        }
        return 1;
    }

    // Comando SET
    redisReply* reply = (redisReply*)redisCommand(context, "SET clave valor");
    std::cout << "SET respuesta: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Comando GET
    reply = (redisReply*)redisCommand(context, "GET clave");
    std::cout << "GET respuesta: " << reply->str << std::endl;
    freeReplyObject(reply);

    // Cerrar conexión
    redisFree(context);
    return 0;
}
