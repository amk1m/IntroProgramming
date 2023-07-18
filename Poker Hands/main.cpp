// ©2023 Nathan Greenfield

#include <iostream>
#include <ctime>

#include "Play.h"

int main(int argc, const char* argv[])
{
	playPoker(std::cin, std::cout, time(nullptr));

	return 0;
}
