#include "Config.hpp"
#include "game.hpp"

#include <iostream>

int main()
{
	std::cout << "JumpHeight: " << JumpHeight << std::endl;
	std::cout << "JumpDuration: " << JumpDuration << std::endl;

	Update();

	return 0;
}