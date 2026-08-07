#include "CLParser.h"
#include "CommandArguments.h"
#include "CommandRegistry.h"
#include <cassert>
#include <sstream>

CLParser::CLParser() : _command_registry(std::make_unique<CommandRegistry>())
{
}

CLParser::~CLParser() = default;

ParserResultHandle CLParser::handle_dirty_command(const std::string& _in_dirty_str)
{
	ParserResultHandle _out_result_handle;

	assert(_command_registry);

	const auto _parsed_tokens = _tokenizer.tokenize(_in_dirty_str);

	if (_parsed_tokens.empty())
	{
		_out_result_handle._result_status = ParserResultStatus::EMPTY_COMMAND;
		return _out_result_handle;
	}

	std::optional<std::pair<const IBaseCommand*, size_t>> _matching_result = std::nullopt;
	try
	{
		_matching_result = find_longest_matching_command(_parsed_tokens);
	}
	catch (const std::exception& _exception)
	{
		_out_result_handle._result_status = ParserResultStatus::INVALID_SYNTAX;
		_out_result_handle._result_message = "Error occurred while parsing command: "+ _in_dirty_str+"\n"
		"Reason: "+ _exception.what();
		return _out_result_handle;
	}

	if (_matching_result == std::nullopt)
	{
		_out_result_handle._result_status = ParserResultStatus::INVALID_SYNTAX;
		_out_result_handle._result_message = "Unknown command";
		return _out_result_handle;
	}

	const auto [_command_ptr, _index_of_additional_args] = _matching_result.value();

	assert(_command_ptr);

	CLParsedCommand _parsed_command;
	_parsed_command._found_command = _command_ptr;
	_parsed_command._matched_command_name = _command_ptr->get_command_meta().name;

	try
	{
		extract_arguments(_parsed_tokens, _index_of_additional_args, _parsed_command);
	}
	catch (const std::exception& _exception)
	{
		_out_result_handle._result_status = ParserResultStatus::INVALID_SYNTAX;
		_out_result_handle._result_message = "Error occurred while parsing command arguments: "+ _in_dirty_str+"\n"
		"Reason: "+ _exception.what();
		return _out_result_handle;
	}

	// TODO add to execute request ptr to core port and
	const auto _execute_result = _command_ptr->execute(_parsed_command);
	if (_execute_result == CommandResult::FAILURE)
	{
		_out_result_handle._result_status = ParserResultStatus::CORE_ERROR;
		_out_result_handle._result_message = "Error while executing request";
		return _out_result_handle;
	}

	_out_result_handle._result_status = ParserResultStatus::SUCCESS;
	return _out_result_handle;
}

std::optional<std::pair<const IBaseCommand*, size_t>> CLParser::find_longest_matching_command(
	const std::vector<std::string>& _in_tokens) const
{
	assert(_command_registry);
	const auto _all_commands = _command_registry->get_all();

	std::optional<std::pair<const IBaseCommand*, size_t>> _best_matching_result;

	for (const IBaseCommand* _command : _all_commands)
	{
		assert(_command);
		const std::string& _command_name = _command->get_command_meta().name;

		std::vector<std::string> _command_name_tokens;

		{
			std::istringstream _isstream(_command_name);
			std::string _part;
			while (_isstream >> _part)
				_command_name_tokens.push_back(_part);
		}

		if (_command_name_tokens.empty() || _command_name_tokens.size() > _in_tokens.size())
		{
			continue;
		}

		bool _has_match = true;
		for (size_t i = 0; i < _command_name_tokens.size(); ++i)
		{
			if (_in_tokens[i] != _command_name_tokens[i])
			{
				_has_match = false;
				break;
			}
		}

		if (!_has_match)
		{
			continue;
		}

		if (!_best_matching_result || _command_name_tokens.size() > _best_matching_result->second)
		{
			_best_matching_result = { _command, _command_name_tokens.size() };
		}
	}

	return _best_matching_result;
}

void CLParser::extract_arguments(
	const std::vector<std::string>& _in_tokens,
	size_t _index_of_args_start,
	CLParsedCommand& _out_result_handle)
{
	for (size_t i = _index_of_args_start; i < _in_tokens.size(); ++i)
	{
		if (const std::string& _token = _in_tokens[i]; _token.starts_with("--") && _token.size() > 2)
		{
			const std::string _key = _token.substr(2);

			if (const auto eq = _key.find('='); eq != std::string::npos)
			{
				_out_result_handle._options[_key.substr(0, eq)] = _key.substr(eq + 1);
				continue;
			}

			if (i + 1 < _in_tokens.size() && !_in_tokens[i + 1].starts_with("-"))
			{
				_out_result_handle._options[_key] = _in_tokens[++i];
			}
			else
			{
				_out_result_handle._options[_key] = "";
			}
		}
		else if (_token.starts_with("-") && _token.size() > 1 && _token[1] != '-')
		{
			if (_token.size() == 2)
			{
				const std::string _key(1, _token[1]);

				if (i + 1 < _in_tokens.size() && !_in_tokens[i + 1].starts_with("-"))
				{
					_out_result_handle._options[_key] = _in_tokens[++i];
				}
				else
				{
					_out_result_handle._options[_key] = "";
				}
			}
			else
			{
				for (size_t j = 1; j < _token.size(); ++j)
				{
					_out_result_handle._options[std::string(1, _token[j])] = "";
				}
			}
		}
		else
		{
			_out_result_handle._positional.push_back(_token);
		}
	}
}
