#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <iostream>
#include <unordered_map>
#include <string>

#include <nlohmann/json.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

using json = nlohmann::json;

class ServidorREST
{

	net::io_context& ioc;
	tcp::acceptor acceptor;

	std::unordered_map<int, std::string> items;
	int id;

	void procesarPeticion(tcp::socket&);
	std::string peticionGET();
	std::string peticionPOST(const std::string&);
	std::string peticionDELETE(int);


public:
	ServidorREST(net::io_context&, unsigned int port);
	void run();
	~ServidorREST();

};

