#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class IBaseCommand;

struct CLParsedCommand
{
	const IBaseCommand* _found_command;
	std::string _matched_command_name; // "task add"
	std::unordered_map<std::string, std::string> _options; // --title -> value
	std::vector<std::string> _positional; // everything without --
};