#include "Logger.hpp"
#include <regex>
#include <iostream>


int main()
{
	util::Log(util::trace, "valami");
	std::regex reg("[0-9]{10}\tvalami");
	std::cout << std::regex_match("0123456789\tvalami", reg);
	std::getchar();
	return 0;
}
