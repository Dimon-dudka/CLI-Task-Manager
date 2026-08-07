#include "CommandRegistry.h"
#include "AddCommand.h"
#include "BaseCommand.h"
#include <cassert>

CommandRegistry::CommandRegistry()
{
	register_command(std::make_unique<AddCommand>());
}

void CommandRegistry::register_command(std::unique_ptr<IBaseCommand> _in_new_command)
{
	assert(_in_new_command);
	const auto _command_name = _in_new_command->get_command_meta()._name;

	if (const auto [_, _emplace_status] = _registered_commands.try_emplace(_command_name, std::move(_in_new_command));
		_emplace_status != true)
	{
		throw std::invalid_argument("Command " + _command_name + " already exists");
	}
}

std::optional<const IBaseCommand*> CommandRegistry::find_command(const std::string& _in_command_name) const
{
	if (const auto _result = _registered_commands.find(_in_command_name); _result != _registered_commands.end())
	{
		assert(_result->second);
		return _result->second.get();
	}

	return std::nullopt;
}

std::vector<const IBaseCommand*> CommandRegistry::get_all() const
{
	std::vector<const IBaseCommand*> _results;
	_results.reserve(_registered_commands.size());

	for (const auto& [_, _command] : _registered_commands)
	{
		_results.push_back(_command.get());
	}

	return _results;
}
