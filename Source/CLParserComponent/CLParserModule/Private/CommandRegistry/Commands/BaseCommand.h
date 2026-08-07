#pragma once

#include <string>



struct CLParsedCommand;
enum class CommandResult
{
	NONE,
	SUCCESS,
	FAILURE,
};

struct CommandMeta
{
	//-Variables-----------------------------------
	std::string name;
	std::string description;
	std::string usage_example;
};

class IBaseCommand
{
	//-Lifecycle-----------------------------------
public:
	virtual ~IBaseCommand() = default;

	//-Methods-------------------------------------
public:
	[[nodiscard]] const virtual CommandMeta& get_command_meta() const = 0;

	[[nodiscard]] virtual CommandResult execute(
		const CLParsedCommand& _in_parsed_command /*const std::shared_ptr<> _application_core_port*/) const = 0;

	//-Variables-----------------------------------
};