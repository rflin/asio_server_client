#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define ASIO_STANDALONE
#include <iostream>
#include <deque>
#include <asio.hpp>
#include "message.h"
#include "participant.h"
#include "room.h"

using asio::ip::tcp;

class session :
	public participant,
	public std::enable_shared_from_this<session> {
public:
	session(tcp::socket socket, room& room) :
		socket_(std::move(socket)),
		room_(room), 
		read_msg_(),
		write_msgs_(){}
	~session();
	void start();
	void deliver(const message& msg) override;
	void do_read_header();
	void do_read_body();
	void do_write();
private:
	tcp::socket socket_;
	room& room_;
	message read_msg_;
	std::deque<message> write_msgs_;
};