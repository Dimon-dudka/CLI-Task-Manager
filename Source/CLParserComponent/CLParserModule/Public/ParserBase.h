#pragma once

#include <string>

// All these structures are public contract and public API
// Reason why it's not in cppm file is because of module importing in the same module
enum class ParserResultStatus
{
	NONE,
	SUCCESS,
	EMPTY_COMMAND,
	INVALID_SYNTAX,
	CORE_ERROR,
	EXIT,
};

struct ParserResultHandle
{
	std::string _result_message = {};
	ParserResultStatus _result_status = ParserResultStatus::NONE;
};

class IParserBase
{
public:
	virtual ~IParserBase() = default;

	[[nodiscard]] virtual ParserResultHandle handle_dirty_command(const std::string& _in_dirty_str) = 0;
};