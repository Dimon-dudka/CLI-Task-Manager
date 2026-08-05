module;

#include <string>
#include <variant>
#include <vector>

export module ApplicationCore;

export enum class HandleAction
{
	UNKNOWN,
	EXIT,
	CONTINUE,
};

export struct HandleResponse
{
	HandleAction _out_action;
	std::variant<std::monostate, std::string> _description;
};

// TODO think, appcore - is BL, and when we gonna switch CL to GUI what is right here is
// something else, like parser module
// and to BL need to be sent specific commands-classes like: AddTaskCommand
export class ICommandInputPort
{
	//-Lifecycle-----------------------------------
public:
	virtual ~ICommandInputPort() = default;

	//-Methods-------------------------------------
	virtual HandleResponse handle_tokens(const std::vector<std::string>& _in_tokens) = 0;

	//-Variables-----------------------------------
};
