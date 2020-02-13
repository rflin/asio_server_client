#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>

//type
#define DATA 11

#define LEAVE_ROOM 2

#define BACK_REQUEST 3
#define BACK_RESPONSE 31
#define BACK_EXECUTE 1

#define SHOW_ALL_ROOM 4
#define SHOW_ALL_ROOM_RESULT 41
#define SELECT_ROOM 42

#define SETROLE 51

#define READY 6
#define READYANDROLE 61

#define END_AND_JUDGE 71
#define WIN 711
#define LOSE 710

#define TEST 9



struct message {
	static const int HEADER_LENGTH = 4;
	static const int MAX_BODY_LENGTH = 256;

	char data_[HEADER_LENGTH + MAX_BODY_LENGTH + 1];
	int body_length_;
public:
	message() = default;
	message(const std::string& r);

	const char* header() const;
	const char* body() const;
	const char* data() const;

	char* header();
	char* body();
	char* data();

	int body_length();
	int length();

	void encode();
	std::pair<int, int> parse();
};