#include "CLParser.h"

CLParserResultHandle CLParser::handle_dirty_command(const std::string& _in_dirty_str)
{
	CLParserResultHandle _out_result_handle;

	const auto _parsed_tokens = _tokenizer.tokenize(_in_dirty_str);

	return _out_result_handle;
}
