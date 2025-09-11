#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

void start_auth_service(io_context& io) {	
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 9000));

	acceptor.async_accept([&](tcp::socket socket) {
		auto buf = std::make_shared<streambuf>();
		async_read_until(socket, *buf, "\n", [buf, &socket](boost::system::error_code, std::size_t) {
			std::istream is(buf.get());
			std::string line;
			std::getline(is, line);
			auto json = nlohmann::json::parse(line);
			std::string response = (json["password"] == "1234") ? "ok\n" : "FAIL\n";
			async_write(socket, buffer(response), [](auto, auto) {});
		});
	});
}