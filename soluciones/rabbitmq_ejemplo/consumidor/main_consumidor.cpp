#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <iostream>

int main() {
    AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create("localhost");

    channel->DeclareQueue("hello-queue", false, true, false, false);

    AmqpClient::Envelope::ptr_t envelope;
    while (true) {
        envelope = channel->BasicGet("hello-queue", true);
        if (envelope) {
            std::cout << "Mensaje recibido: " << envelope->Message()->Body() << std::endl;
        }
    }

    return 0;
}
