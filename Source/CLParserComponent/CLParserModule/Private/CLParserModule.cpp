module;

#include "CLTokenizer.h"
#include <cassert>
#include <memory>
#include <string>

module CLParserModule;

class CLParser final : public ICLParserInput
{
public:
	[[nodiscard]] CLParserResultHandle handle_dirty_command(const std::string& _in_dirty_str) override;

private:
	CLTokenizer _tokenizer;
};

#pragma region CLParserModule
CLParserModule::CLParserModule()
{
	_primary_port = std::make_shared<CLParser>();
}

std::shared_ptr<ICLParserInput> CLParserModule::get_input_port() const
{
	assert(_primary_port);
	return _primary_port;
}
#pragma endregion


#pragma region CLParser
CLParserResultHandle CLParser::handle_dirty_command(const std::string& _in_dirty_str)
{
	CLParserResultHandle _out_result_handle;

	const auto _parsed_tokens = _tokenizer.tokenize(_in_dirty_str);

	return _out_result_handle;
}

#pragma endregion