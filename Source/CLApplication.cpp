#include "CLApplication.h"
#include <iostream>
#include <memory>

import CLInputModule;
import CLParserModule;

void CLApplication::start()
try
{
	const CLParserModule _cl_parser;

	CLInputComponent _cl_input_component(_cl_parser.get_input_port());

	_cl_input_component.handle_input();
}
catch (const std::exception& _exception)
{
	const int pid = getpid();

	std::cout << "Unhandled exception: " << _exception.what() << std::endl;
	std::cout << "Calling terminate of process " << pid << std::endl;
	abort();
}
