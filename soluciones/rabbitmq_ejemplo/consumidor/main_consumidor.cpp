#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <iostream>
#include <cstring>

void check_reply(amqp_rpc_reply_t reply, const std::string& context) {
    if (reply.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << "Error en " << context << ": tipo de respuesta inesperado." << std::endl;
        exit(1);
    }
}

int main() {
    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(conn);
    if (!socket) {
        std::cerr << "Error al crear socket TCP." << std::endl;
        return 1;
    }

    int status = amqp_socket_open(socket, "localhost", 5672);
    if (status != AMQP_STATUS_OK) {
        std::cerr << "Error al conectar con RabbitMQ: " << amqp_error_string2(status) << std::endl;
        return 1;
    }

    check_reply(amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest"), "login");

    amqp_channel_open(conn, 1);
    check_reply(amqp_get_rpc_reply(conn), "abrir canal");

    // Declarar la cola explícitamente
    amqp_queue_declare(conn, 1, amqp_cstring_bytes("cola_demo"),
        0,    // passive
        0,    // durable
        0,    // exclusive
        0,    // auto-delete
        amqp_empty_table);
    check_reply(amqp_get_rpc_reply(conn), "declarar cola");

    // Iniciar consumo
    amqp_basic_consume(conn, 1, amqp_cstring_bytes("cola_demo"),
        amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
    check_reply(amqp_get_rpc_reply(conn), "iniciar consumo");

    std::cout << "Esperando mensajes en cola_demo..." << std::endl;

    while (true) {
        amqp_envelope_t envelope;
        amqp_maybe_release_buffers(conn);
        amqp_rpc_reply_t res = amqp_consume_message(conn, &envelope, NULL, 0);

        if (res.reply_type == AMQP_RESPONSE_NORMAL) {
            std::string cuerpo((char*)envelope.message.body.bytes, envelope.message.body.len);
            std::cout << "Mensaje recibido: " << cuerpo << std::endl;
            amqp_destroy_envelope(&envelope);
        }
        else {
            std::cerr << "Error al consumir mensaje: tipo " << res.reply_type << std::endl;
            break;
        }
    }

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
    return 0;
}
