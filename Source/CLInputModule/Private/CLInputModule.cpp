module;

#include "CLReader.h"
#include "ParserBase.h"
#include <cassert>
#include <iostream>
#include <memory>

module CLInputModule;

CLInputComponent::CLInputComponent(const std::shared_ptr<IParserBase>& _in_new_parser_input)
	: _parser_adapter(_in_new_parser_input)
{
	_input_reader = std::make_unique<CLReader>();
}

void CLInputComponent::handle_input()
{
	_is_reading = true;

	while (_is_reading)
	{
		assert(_input_reader);
		assert(_parser_adapter);

		try
		{
			const auto _non_parsed_input = _input_reader->read_input();
			const auto _operation_result = _parser_adapter->handle_dirty_command(_non_parsed_input);

			handle_work_result(_operation_result);
		}
		catch (const std::exception& _exception)
		{
			std::cout << "Exception occurred: " << _exception.what() << std::endl;
			_is_reading = false;
			break;
		}
	}
}

void CLInputComponent::handle_work_result(const ParserResultHandle& _parser_result)
{
	switch (_parser_result._result_status)
	{
		case ParserResultStatus::SUCCESS:
		{
			return;
		}
		case ParserResultStatus::INVALID_SYNTAX:
		{
			std::cout << "Invalid syntax detected: " << _parser_result._result_message << std::endl;
			break;
		}
		case ParserResultStatus::CORE_ERROR:
		{
			std::cout << "Error by executing user request: " << _parser_result._result_message << std::endl;
		}
		case ParserResultStatus::EXIT:
		{
			_is_reading = false;
			break;
		}
		case ParserResultStatus::NONE:
			[[fallthrough]];
		default:
		{
			// TODO think about another way
			assert(false);
			_is_reading = false;
			throw std::runtime_error("Unknown result status");
			break;
		}
	}
}
