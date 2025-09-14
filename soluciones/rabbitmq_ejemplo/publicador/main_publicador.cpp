#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>


int main() {
    // Conectar a RabbitMQ
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create();
    channel->DeclareExchange("hello-exchange", AmqpClient::Channel::EXCHANGE_TYPE_FANOUT); // Crear un exchange de tipo fanout
    channel->DeclareQueue("hello-queue", true); // Crear una cola
    channel->BindQueue("hello-queue", "hello-exchange"); // Enlazar la cola al exchange

    // Enviar un mensaje
    std::string message = "¡Hola desde C++!";
    channel->BasicPublish("hello-exchange", "hello-queue", message);

    std::cout << "Mensaje enviado: " << message << std::endl;

    return 0;
}
