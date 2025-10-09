// rabbit.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
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

    std::cout << "Guest Conectado ... " << std::endl;

    // Abrir el canal
    amqp_channel_open(con, 1);
    amqp_rpc_reply_t channel_reply = amqp_get_rpc_reply(con);
    if (channel_reply.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << " error en el canal" << std::endl;
        return;
    }

    // Abrir la cola, si no existe la crea:
    amqp_bytes_t queue = amqp_cstring_bytes("test_queue");
    amqp_queue_declare(con, 1, queue, 0, 0, 0, 1, amqp_empty_table);
    amqp_get_rpc_reply(con);

    std::string mensaje;
    for (int i = 0; i < 5; i++) {
        mensaje = "mensaje desde el productor " + std::to_string((i+1));

        // Crear el mensaje:
        amqp_bytes_t message = amqp_cstring_bytes(mensaje.c_str());

        // publicar el mensaje:
        amqp_basic_publish(con, 1, amqp_empty_bytes, queue, 0, 0, nullptr, message);

        std::cout << "mensaje enviado " << std::endl;
    }

    // liberar recursos:
    amqp_channel_close(con, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(con, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(con);
}

void consumidor() {

}


int main()
{
    productor();
    consumidor();
    return 0;

}
