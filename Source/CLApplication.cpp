#include "CLApplication.h"
#include <iostream>
#include <memory>

import CLModule;

void CLApplication::start()
try
{
	//TODO add out port for reader
	CLComponent _cl_component;
	_cl_component.handle_input();
}
catch (const std::exception& _exception)
{
	const int pid = getpid();

	std::cout << "Unhandled exception: " << _exception.what() << std::endl;
	std::cout << "Calling terminate of process " << pid << std::endl;
	abort();
}
