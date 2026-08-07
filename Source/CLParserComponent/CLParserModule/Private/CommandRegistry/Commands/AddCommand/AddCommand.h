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
	inline static const CommandMeta _command_meta { .name = "task add",
													.description = "Create a new task",
													.usage_example =
														"task add --title <title> "
														"[--description <description>]" };
};
