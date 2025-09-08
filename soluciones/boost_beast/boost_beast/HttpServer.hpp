#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class HttpServer {
public:
	HttpServer(net::io_context& ioc, unsigned short port);
	void run();

private:
	void handle_request(tcp::socket& socket);

	net::io_context& ioc_;
	tcp::acceptor acceptor_;
};