#include "server.h"

void server::start() {
	std::cout << "server start...\n";
	do_accept();
	io_context_.run();
}
void server::do_accept() {
	acceptor_.async_accept(
		[this](std::error_code ec, tcp::socket socket) {
			if (!ec) {
				std::cout << "new connection: "
					<< socket.remote_endpoint().address()
					<< " "
					<< socket.remote_endpoint().port()
					<< std::endl;
				std::make_shared<session>(std::move(socket), room_)->start();
			}
			do_accept();
		}
	);
}