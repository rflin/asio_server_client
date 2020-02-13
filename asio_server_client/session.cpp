#include "session.h"
session::~session() {
	std::cout << "session dead..." << std::endl;
}
void session::start() {
	room_.join(shared_from_this());
	do_read_header();
}
void session::deliver(const message& msg) {
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress) {
		do_write();
	}
}
void session::do_read_header() {
	auto self(shared_from_this());
	asio::async_read(
		socket_,
		asio::buffer(read_msg_.header(), message::HEADER_LENGTH),
		[this, self](std::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				read_msg_.encode();
				do_read_body();
			}
			else {
				room_.leave(shared_from_this());
			}
		}
	);
}
void session::do_read_body() {
	auto self(shared_from_this());
	asio::async_read(
		socket_,
		asio::buffer(read_msg_.body(), read_msg_.body_length()),
		[this, self](std::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				auto result = read_msg_.parse();
				if (result.first == TEST) {
					//printf("received: %2d %4d\n", result.first, result.second);
					int data = result.second;
					char information[64];
					sprintf(information, " %d %d", TEST, result.second);
					room_.deliver_all(message(information));
					if (room_.count % 1000 == 0) {
						printf("count = %d\n", room_.count);
					}
					
				}
				do_read_header();
			}
			else {
				room_.leave(shared_from_this());
			}
		}
	);
}
void session::do_write() {
	auto self(shared_from_this());
	asio::async_write(
		socket_,
		asio::buffer(write_msgs_.front().data(), write_msgs_.front().length()),
		[this, self](std::error_code ec, std::size_t /*length*/) {
			if (!ec) {
				write_msgs_.pop_front();
				if (!write_msgs_.empty()) {
					do_write();
				}
			}
			else {
				room_.leave(shared_from_this());
			}
		}
	);
}