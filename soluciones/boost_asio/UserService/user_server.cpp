#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;

void start_user_service(io_context& io) {
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 9001));

	acceptor.async_accept([&](tcp::socket socket) {
		auto buf = std::make_shared<streambuf>();
		async_read_until(socket, *buf, "\n", [buf, &socket](boost::system::error_code, std::size_t) {
			std::istream is(buf.get());
			std::string line;
			std::getline(is, line);
			auto json = nlohmann::json::parse(line);
			std::string user_id = json["user_id"];
			nlohmann::json response = { {"name","Juan"}, {"id",user_id} };
			async_write(socket, buffer(response.dump() + "\n"), [](auto, auto) {});
		});
	});
}

int main() {
	boost::asio::io_context contexto;

	std::cout << "Servidor asincrono: user_service, ejecutandose en el puerto 9001" << std::endl;
	start_user_service(contexto);
	contexto.run();
}
