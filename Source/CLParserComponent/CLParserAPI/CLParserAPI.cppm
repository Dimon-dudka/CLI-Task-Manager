module;

#include <string>

export module CLParserAPI;

export enum class CLParserResultStatus
{
	SUCCESS,
	INVALID_SYNTAX,
	CORE_ERROR,
	EXIT,
};

export struct CLParserResultHandle
{
	std::string _result_message = {};
	CLParserResultStatus _result_status = CLParserResultStatus::SUCCESS;
};

export class ICLParserInput
{
public:
	virtual ~ICLParserInput() = default;

	[[nodiscard]] virtual CLParserResultHandle handle_dirty_command(const std::string& _in_dirty_str) = 0;
};