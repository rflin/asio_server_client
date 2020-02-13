#include "room.h"
void room::join(std::shared_ptr<participant> p) {
	participants_.insert(p);
}
void room::leave(std::shared_ptr<participant> p) {
	participants_.erase(p);
}
void room::deliver_all(const message& msg) {
	count += 1;
	for (auto p : participants_) {
		p->deliver(msg);
	}
}