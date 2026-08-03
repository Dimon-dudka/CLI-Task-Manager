module;

#include "CLReader.h"
#include <cassert>
#include <iostream>
#include <memory>

module CLModule;

CLComponent::CLComponent()
{
	_input_reader = std::make_unique<CLReader>();
	_tokenizer = std::make_unique<CLTokenizer>();
}

void CLComponent::handle_input()
{
	bool _is_reading = true;

	while (_is_reading)
	{
		assert(_input_reader);
		assert(_tokenizer);

		try
		{
			const auto _non_parsed_input = _input_reader->read_input();
			const auto _parsed_tokens = _tokenizer->tokenize(_non_parsed_input);
		}
		catch (const std::exception& _exception)
		{
			std::cout << "Exception occurred: " << _exception.what() << std::endl;
			_is_reading = false;
			break;
		}
	}
}