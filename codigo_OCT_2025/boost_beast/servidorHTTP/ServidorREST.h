#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <nlohmann/json.hpp>

#include <iostream>
#include <unordered_map>
#include <string>

 
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

using tcp = net::ip::tcp;
using json = nlohmann::json;


class ServidorREST
{
public:
	ServidorREST(net::io_context& ioc, unsigned short port);
	void run();

private:
	void handle_request(tcp::socket& socket);
	std::string peticionGet();
	std::string peticionPost(const std::string);
	std::string peticionDelete(int);

	net::io_context& ioc_;
	tcp::acceptor acceptor_;

	std::unordered_map<int, std::string> items;
	int next_id = 1;
};

