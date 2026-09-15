#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <string>
#include <unordered_map>
#include <iostream>

#include <nlohmann/json.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

using tcp = net::ip::tcp;
using json = nlohmann::json;

class ServidorREST
{
	int id;
	std::unordered_map<int, std::string> items;

	// Contexto E/S:
	net::io_context& ioc;

	// Para aceptar los clientes:
	tcp::acceptor acceptor;

public:
	ServidorREST(net::io_context& ioc, unsigned int port);
	void run();
	~ServidorREST();
};

