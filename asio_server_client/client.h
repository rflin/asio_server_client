#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ASIO_STANDALONE
#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <asio.hpp>
#include "message.h"

using asio::ip::tcp;

class client {
public:
	int count = 0;
	client() = delete;
	client(const std::string& ip, const std::string& port) : 
		io_context_(),
		resolver_(io_context_),
		query_(ip, port),
		endpoints_(resolver_.resolve(query_)),
		socket_(io_context_),
		read_msg_(),
		write_msgs_(){}
	void start();
	void write(const message& msg);
	void close();
private:
	void do_connect();
	void do_read_header();
	void do_read_body();
	void do_write();

	asio::io_context io_context_;
	tcp::resolver resolver_;
	tcp::resolver::query query_;
	tcp::resolver::results_type endpoints_;
	tcp::socket socket_;

	message read_msg_;
	std::deque<message> write_msgs_;
};