#pragma once

#include <string>
#include <vector>

/*
 * Because the only one purpose is to return array of tokens - no need in interface
 */
class CLTokenizer
{
	//-Lifecycle-----------------------------------
	//-Methods-------------------------------------
public:
	[[nodiscard]] std::vector<std::string> tokenize(const std::string_view& _in_string);

	//-Variables-----------------------------------
};
