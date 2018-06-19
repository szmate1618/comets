#include "Logger.hpp"

#include <regex>
#include <iostream>
#include <thread>


void call_from_thread() {
	std::cout << "Hello, World" << std::endl;

}

int main()
{
	util::Log(util::trace, "valami");
	std::regex reg("[0-9]{10}\tvalami");
	std::cout << std::regex_match("0123456789\tvalami", reg);

	std::thread threads[10];
	threads[0] = std::thread(call_from_thread);
	threads[0].join();

	std::getchar();
	return 0;
}
