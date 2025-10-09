// rabbit.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <amqp.h>
#include <amqp_tcp_socket.h>


void productor() {
    const char* hostname = "localhost";
    int port = 5672;

    // Crear una conexion y el socket:
    amqp_connection_state_t con = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(con);

    if (!socket) {
        std::cerr << " error en el socket" << std::endl;
        return;
    }

    int status = amqp_socket_open(socket, hostname, port);
    if (status != AMQP_STATUS_OK) {
        std::cerr << " error al abrir el socket" << amqp_error_string2(status) << std::endl;
        return;
    }

    amqp_rpc_reply_t login = amqp_login(con, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
    if (login.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << " error en login" << std::endl;
        return;
    }

}

void consumidor() {

}


int main()
{
    productor();
    consumidor();
    return 0;

}
