#pragma once

#include <optional>
#include <string>
#include <vector>


struct CLParsedCommand;

enum class CommandResult
{
	NONE,
	SUCCESS,
	FAILURE,
};

struct CommandOptionMeta
{
	std::string _long_name;
	std::string _description;

	std::optional<char> _short_name;

	bool _requires_value = false;
	bool _required = false;
};

struct CommandMeta
{
	//-Variables-----------------------------------
	std::string _name;
	std::string _description;
	std::string _usage_example;

	std::vector<CommandOptionMeta> _options;
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