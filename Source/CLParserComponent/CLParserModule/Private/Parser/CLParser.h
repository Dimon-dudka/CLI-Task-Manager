#pragma once

#include "CLTokenizer.h"

import CLParserAPI;


class CLParser final : public ICLParserInput
{
	//-Lifecycle-----------------------------------
	//-Methods-------------------------------------
public:
	[[nodiscard]] virtual CLParserResultHandle handle_dirty_command(const std::string& _in_dirty_str) override;

	//-Variables-----------------------------------

private:
	CLTokenizer _tokenizer;
};
