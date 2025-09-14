#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    const char* hostname = "localhost";
    int port = 5672;

    // Crear conexión
    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(conn);
    if (!socket) {
        fprintf(stderr, "Error creando socket\n");
        return 1;
    }

    if (amqp_socket_open(socket, hostname, port)) {
        fprintf(stderr, "Error abriendo socket\n");
        return 1;
    }

    // Login
    amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn);

    // Declarar cola
    amqp_queue_declare(conn, 1, amqp_cstring_bytes("mi_cola"),
        0, 0, 0, 1, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    // Crear y enviar mensaje
    amqp_bytes_t cola = amqp_cstring_bytes("mi_cola");
    amqp_bytes_t cuerpo = amqp_cstring_bytes("Hola desde C con rabbitmq-c");

    amqp_basic_publish(conn, 1, amqp_empty_bytes(), cola, 0, 0, NULL, cuerpo);


    printf("Mensaje enviado\n");

    // Cerrar conexión
    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);

    return 0;
}
