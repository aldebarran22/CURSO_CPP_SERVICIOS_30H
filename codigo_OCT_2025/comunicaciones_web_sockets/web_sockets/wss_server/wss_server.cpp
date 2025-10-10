// ws_servidor.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <thread>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

#define PORT 8443

int main()
{
	net::io_context ioc;
	ssl::context ctx(ssl::context::tlsv12_server);

	// Pasar los dos ficheros generados con openssl:
	ctx.use_certificate_chain_file("cert.pem");
	ctx.use_private_key_file("key.pem", ssl::context::file_format::pem);

	tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), PORT));
	std::cout << "Servidor WSS escuchando en puerto: " << PORT << std::endl;




}
