#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <iostream>
#include <cstring>

int main() {
    // Crear conexión
    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(conn);
    amqp_socket_open(socket, "localhost", 5672);

    // Autenticación
    amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");

    // Abrir canal
    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn);

    // Declarar cola
    amqp_queue_declare(conn, 1, amqp_cstring_bytes("cola_demo"),
        0, 0, 0, 1, amqp_empty_table);
    amqp_get_rpc_reply(conn);

    // Crear mensaje
    std::string mensaje = R"({"mensaje":"Hola desde librabbitmq"})";
    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG;
    props.content_type = amqp_cstring_bytes("application/json");

    // Publicar
    amqp_basic_publish(conn, 1,
        amqp_cstring_bytes(""),  // default exchange
        amqp_cstring_bytes("cola_demo"),
        0, 0, &props,
        amqp_cstring_bytes(mensaje.c_str()));

    std::cout << "Mensaje publicado en cola_demo" << std::endl;

    // Cerrar canal y conexión
    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);

    return 0;
}
