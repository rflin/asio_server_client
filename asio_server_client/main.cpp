#define _CRT_SECURE_NO_WARNINGS
#define ASIO_STANDALONE
#include <iostream>
#include <string>
#include <asio.hpp>
#include <thread>
#include "server.h"
#include "client.h"

#define SERVER

int main(int argc, char* argv[])
{
	try {
#ifdef SERVER
		server svr(5555);
		svr.start();
#else
		client c("127.0.0.1", "5555");
		c.count = 0;
		std::thread t([&c]() {c.start(); });
		std::this_thread::sleep_for(std::chrono::duration<int>(5));
		for (int i = 0; i < 10000; ++i) {
			c.write(message(" 9 " + std::to_string(i + 1) + "\n"));
		}
		while (true);
		t.join();

#endif	
	}
	catch (std::exception e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	return 0;
}