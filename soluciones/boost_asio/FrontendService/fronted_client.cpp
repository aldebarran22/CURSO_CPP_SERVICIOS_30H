#include <boost/asio.hpp>

#include <iostream>
#include "json_util.hpp"

using namespace boost::asio;
using ip::tcp;

std::string send_request(io_context& io, const std::string& host, int port, const std::string& msg) {
	tcp::socket socket(io);
	socket.connect(tcp::endpoint(ip::make_address(host), port));
	write(socket, buffer(msg + "\n"));
	streambuf buf;
	read_until(socket, buf, "\n");

	std::istream is(&buf);
	std::string response;
	std::getline(is, response);
	return response;
}

int main() {
	io_context io;

	std::string auth_msg = build_auth_request("juan", "1234");
	std::string auth_response = send_request(io, "127.0.0.1", 9000, auth_msg);
	std::cout << "Auth response: " << auth_response << std::endl;

	if (auth_response == "OK") {
		std::string user_msg = build_auth_request("42");
		std::string user_response = send_request(io, "127.0.0.1", 9001, user_msg);
		std::cout << "User response: " << user_response << std::endl;
	}
	return 0;
}