#include "CLReader.h"
#include <iostream>

std::string CLReader::read_input()
{
	std::string _user_input;

	std::cout << "CLI>" << std::flush;

	std::getline(std::cin, _user_input);
	return _user_input;
}