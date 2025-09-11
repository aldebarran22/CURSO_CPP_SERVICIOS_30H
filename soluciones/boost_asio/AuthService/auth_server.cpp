#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace boost::asio;
using ip::tcp;


class AuthService {

public:
    AuthService(io_context& io): acceptor_(io, tcp::endpoint(tcp::v4(), 9000)) {
        start_accept();
    }

private:
    void start_accept() {
        socket_ = std::make_unique<tcp::socket>(acceptor_.get_executor().context());
        acceptor_.async_accept(*socket_, [this](boost::system::error_code ec) {
            if (!ec) {
                handle_client();
            }
            start_accept();  // Aceptar siguiente conexión
            });
    }

    void handle_client() {
        auto buf = std::make_shared<streambuf>();
        async_read_until(*socket_, *buf, "\n", [buf, this](boost::system::error_code, std::size_t) {
            std::istream is(buf.get());
            std::string line;
            std::getline(is, line);

            try {
                auto json = nlohmann::json::parse(line);
                std::string response = (json["password"] == "1234") ? "ok\n" : "FAIL\n";
                async_write(*socket_, buffer(response), [](auto, auto) {});
            }
            catch (...) {
                async_write(*socket_, buffer("ERROR\n"), [](auto, auto) {});
            }
            });
    }

    tcp::acceptor acceptor_;
    std::unique_ptr<tcp::socket> socket_;
};

int main() {
    boost::asio::io_context io;
    std::cout << "AuthService escuchando en el puerto 9000..." << std::endl;

    try {
        AuthService server(io);
        io.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Excepción capturada: " << ex.what() << std::endl;
    }
}

