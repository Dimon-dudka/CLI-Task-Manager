module;

#include "CLReader.h"
#include <c++/13/cassert>
#include <iostream>
#include <memory>

module CLModule;

CLComponent::CLComponent()
{
	_input_reader = std::make_unique<CLReader>();
}

void CLComponent::handle_input()
{
	bool _is_reading = true;
	while (_is_reading)
	{
		assert(_input_reader);

		try
		{
			const auto _non_parsed_input = _input_reader->read_input();
		}
		catch (const std::exception& _exception)
		{
			std::cout << "Exception occurred: " << _exception.what() << std::endl;
			_is_reading = false;
			break;
		}
	}
}