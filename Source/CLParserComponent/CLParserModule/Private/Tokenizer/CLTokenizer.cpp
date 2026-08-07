#include "CLTokenizer.h"

namespace
{
	constexpr int _init_res_vec_size = 5;
}

std::vector<std::string> CLTokenizer::tokenize(const std::string& _in_string)
{
	std::vector<std::string> _result;
	_result.reserve(_init_res_vec_size);

	std::string _current_token;

	bool _is_inside_quotes = false;

	for (const auto& _in_char : _in_string)
	{
		if (_in_char == '"')
		{
			_is_inside_quotes = !_is_inside_quotes;
			continue;
		}

		if (std::isspace(static_cast<unsigned char>(_in_char)) && !_is_inside_quotes)
		{
			if (!_current_token.empty())
			{
				_result.push_back(std::move(_current_token));
				_current_token.clear();
			}

			continue;
		}

		_current_token += _in_char;
	}

	if (!_current_token.empty())
	{
		_result.push_back(std::move(_current_token));
	}

	return _result;
}