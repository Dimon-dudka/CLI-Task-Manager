#include "CLApplication.h"
#include <iostream>
#include <memory>

import CLInputModule;
import CLParserModule;
//import CLParserAPI;

void CLApplication::start()
try
{
	const CLParserModule _cl_parser;

	const auto tmp = _cl_parser.get_input_port();
	CLInputComponent _cl_input_component(tmp);

	_cl_input_component.handle_input();
}
catch (const std::exception& _exception)
{
	const int pid = getpid();

	std::cout << "Unhandled exception: " << _exception.what() << std::endl;
	std::cout << "Calling terminate of process " << pid << std::endl;
	abort();
}
