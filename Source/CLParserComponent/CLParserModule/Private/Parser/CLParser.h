#pragma once

#include "BaseCommand.h"
#include "CLTokenizer.h"
#include "ParserBase.h"
#include <memory>
#include <optional>

struct CLParsedCommand;
class CommandRegistry;

class CLParser final : public IParserBase
{
// tests section
#ifdef TESTS_ENABLED
	friend class CLParserTests;
#endif

	//-Lifecycle-----------------------------------
public:
	CLParser();
	virtual ~CLParser() override;

	//-Methods-------------------------------------
public:
	[[nodiscard]] virtual ParserResultHandle handle_dirty_command(const std::string& _in_dirty_str) override;

private:
	[[nodiscard]] std::optional<std::pair<const IBaseCommand*, size_t>> find_longest_matching_command(
		const std::vector<std::string>& _in_tokens) const;

	void extract_arguments(
		const std::vector<std::string>& _in_tokens,
		size_t _index_of_args_start,
		CLParsedCommand& _out_result_handle);

	//-Variables-----------------------------------
private:
	CLTokenizer _tokenizer;

	std::unique_ptr<CommandRegistry> _command_registry;
};
