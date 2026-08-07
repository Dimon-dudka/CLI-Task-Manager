#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class IBaseCommand;

class CommandRegistry
{
	//-Lifecycle-----------------------------------
public:
	CommandRegistry();

	//-Methods-------------------------------------
public:
	void register_command(std::unique_ptr<IBaseCommand> _in_new_command);

	[[nodiscard]] std::optional<const IBaseCommand*> find_command(const std::string& _in_command_name) const;
	[[nodiscard]] std::vector<const IBaseCommand*> get_all() const;

	//-Variables-----------------------------------
private:
	std::unordered_map<std::string, std::unique_ptr<IBaseCommand>> _registered_commands;
};
