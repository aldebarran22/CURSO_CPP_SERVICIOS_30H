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
	// Para la gestión del mapa:
	int id;
	std::unordered_map<int, std::string> items;

	// Contexto de e/s:
	net::io_context& ioc;

	// Acceptor para aceptar clientes:
	tcp::acceptor acceptor;

	// Metodos relacionados:
	void procesarPeticion(tcp::socket&);
	std::string peticionGET();
	std::string peticionPOST(const std::string&);
	std::string peticionDELETE(int);

public:
	ServidorREST(net::io_context& ioc, unsigned int port);
	void run();
	~ServidorREST();

};

