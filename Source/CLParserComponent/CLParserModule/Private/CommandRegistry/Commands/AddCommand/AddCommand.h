#pragma once

#include "BaseCommand.h"


class AddCommand final : public IBaseCommand
{
	//-Lifecycle-----------------------------------
	//-Methods-------------------------------------
public:
	[[nodiscard]] const virtual CommandMeta& get_command_meta() const override;
	[[nodiscard]] virtual CommandResult execute(
		const CLParsedCommand& _in_parsed_command /*const std::shared_ptr<> _application_core_port*/) const;

	//-Variables-----------------------------------
private:
	inline static const CommandMeta _command_meta { ._name = "task add",

													._description = "Create a new task",

													._usage_example =
														"task add --title <title> "
														"[--description <description>]",

													._options = { { ._long_name = "title",
																	._short_name = 't',
																	._requires_value = true,
																	._required = true,
																	._description = "Task title" },
																  { ._long_name = "description",
																	._short_name = 'd',
																	._requires_value = true,
																	._required = false,
																	._description = "Task description" },
																  { ._long_name = "help",
																	._short_name = 'h',
																	._requires_value = false,
																	._required = false,
																	._description = "Show help" } } };
};
