#include "message.h"
message::message(const std::string & r) {
	body_length_ = r.size();
	sprintf(data(), "%04d%s", body_length_, r.c_str());
}
const char* message::header() const {
	return data_;
}
const char* message::body() const {
	return data_ + HEADER_LENGTH;
}
const char* message::data() const {
	return data_;
}

char* message::header() {
	return data_;
}
char* message::body() {
	return data_ + HEADER_LENGTH;
}
char* message::data() {
	return data_;
}

int message::body_length() {
	return body_length_;
}
int message::length() {
	return body_length_ + HEADER_LENGTH;
}
void message::encode() {
	char new_header[HEADER_LENGTH + 1] = "";
	strncpy(new_header, header(), HEADER_LENGTH);
	new_header[HEADER_LENGTH] = '\0';

	body_length_ = std::atoi(new_header);
}
std::pair<int, int> message::parse() {
	std::pair<int, int> result;
	std::string bodyX(body(), body() + body_length());
	auto r = sscanf(bodyX.c_str(), " %d %d", &result.first, &result.second);
	return result;
}