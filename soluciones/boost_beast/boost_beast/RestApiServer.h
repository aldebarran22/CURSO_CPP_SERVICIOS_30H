#pragma once

#include <boost/beast/core.hpp>           // Core de Beast: buffers, streams
#include <boost/beast/http.hpp>           // Manejo de HTTP: request, response
#include <boost/beast/version.hpp>        // Versión de Beast
#include <boost/asio/ip/tcp.hpp>          // TCP con Boost.Asio
#include <boost/asio/io_context.hpp>      // Contexto de I/O

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <nlohmann/json.hpp>			  // Para manejar json

using json = nlohmann::json;
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;


class RestApiServer
{
public:
	RestApiServer(net::io_context& ioc, unsigned short port);
	void run();

private:
	void handle_request(tcp::socket& socket);
	std::string route_get_items();
	std::string route_post_item(const std::string& body);
	std::string route_delete_item(int id);

	boost::asio::ip::tcp::acceptor acceptor_;
	std::unordered_map<int, std::string> items_;
	int next_id_ = 1;

};

