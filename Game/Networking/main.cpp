#include <iostream>

int main()
{
	std::cout << ((0xAABBCCDD & (0xFF << 16)) >> 16) << std::endl;
	//std::cout << (256 >> 4);
	std::cout << (123 << 24) << std::endl;
	std::cout << (123 * 256 * 256 * 256) << std::endl;
	std::getchar();
}