#pragma once
class participant {
public:
	virtual void deliver(const message& msg) = 0;
};