#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ASIO_STANDALONE
#include <set>
#include <vector>
#include <deque>
#include <asio.hpp>
#include "room.h"
#include "session.h"

using asio::ip::tcp;

class server {
public:
	server(int port) :
		io_context_(),
		endpoint_(tcp::v4(), port),
		acceptor_(io_context_, endpoint_),
		room_(){}
	void start();
private:
	void do_accept();
	asio::io_context io_context_;
	tcp::endpoint endpoint_;
	tcp::acceptor acceptor_;
	room room_;
};