#include <iostream>
#include <zmq.hpp>

void testZeroMQ() {
	zmq::context_t context(1);
}

int main() {
	testZeroMQ();
	return 0;
}
