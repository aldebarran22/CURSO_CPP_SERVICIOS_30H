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


void do_session(tcp::socket socket, ssl::context& ctx) {

	try {
		websocket::stream<beast::ssl_stream<tcp::socket>> ws(std::move(socket), ctx);
		ws.next_layer().handshake(ssl::stream_base::server);
		ws.accept();

		for (;;) {
			beast::flat_buffer buffer;
			ws.read(buffer);
			ws.text(ws.got_text());
			ws.write(buffer.data()); // Hace un echo de la cadena recibida.
		}

	}
	catch (const beast::system_error& se) {
		if (se.code() != websocket::error::closed) {
			std::cerr << "Error en session: " << se.what() << std::endl;
		}
		else {
			std::cout << "Cliente desconectado" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error inesperado " << e.what() << std::endl;
	}
}

int main()
{
	try {
		net::io_context ioc;
		ssl::context ctx(ssl::context::tlsv12_server);

		// Pasar los dos ficheros generados con openssl:
		ctx.use_certificate_chain_file("cert.pem");
		ctx.use_private_key_file("key.pem", ssl::context::file_format::pem);

		tcp::acceptor acceptor(ioc, tcp::endpoint(tcp::v4(), PORT));
		std::cout << "Servidor WSS escuchando en puerto: " << PORT << std::endl;

		for (;;) {
			tcp::socket socket(ioc);
			acceptor.accept(socket);
			std::thread{ do_session, std::move(socket), std::ref(ctx) }.detach();
		}

	}
	catch (const std::exception& e) {
		std::cerr << "Error inesperado " << e.what() << std::endl;
	}

	return 0;
}
