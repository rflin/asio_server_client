#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include "message.h"
#include "participant.h"
class room {
public:
	void join(std::shared_ptr<participant> p);
	void leave(std::shared_ptr<participant> p);
	void deliver_all(const message& msg);
private:
	std::set<std::shared_ptr<participant>> participants_;
public:
	int count = 0;
};