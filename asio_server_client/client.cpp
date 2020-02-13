#include "client.h"

void client::start() {
	do_connect();
	io_context_.run();
}

void client::write(const message& msg) {
	asio::post(
		io_context_,
		[this, msg]() {
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress) {
				do_write();
			}
		}
	);
}

void client::close() {
	asio::post(io_context_, [this]() {socket_.close(); });
}

void client::do_connect() {
	asio::async_connect(
		socket_,
		endpoints_,
		[this](std::error_code ec, tcp::endpoint) {
			if (!ec) {
				do_read_header();
			}
		}
	);
}
void client::do_read_header() {
	asio::async_read(
		socket_,
		asio::buffer(read_msg_.header(), message::HEADER_LENGTH),
		[this](std::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				read_msg_.encode();
				do_read_body();
			}
			else {
				socket_.close();
			}
		}
	);
}
void client::do_read_body() {
	asio::async_read(
		socket_,
		asio::buffer(read_msg_.body(), read_msg_.body_length()),
		[this](std::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				auto result = read_msg_.parse();
				do_read_header();
			}
			else {
				socket_.close();
			}
		}
	);
}
void client::do_write() {
	asio::async_write(
		socket_,
		asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
		[this](std::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				count += 1;
				write_msgs_.pop_front();
				if (!write_msgs_.empty()) {
					do_write();
				}
			}
			else {
				socket_.close();
			}
		}
	);
}