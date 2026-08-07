#include "CLParser.h"
#include "CommandRegistry/Contract/CommandArguments.h"
#include <gtest/gtest.h>

class CLParserTests : public testing::Test
{
	//-Lifecycle-----------------------------------
protected:
	void SetUp() override
	{
		Test::SetUp();

		_parser = std::make_unique<CLParser>();
	}

	void TearDown() override
	{
		Test::TearDown();
	}

	//-Methods-------------------------------------
protected:
	[[nodiscard]] auto find_longest_matching_command(const std::vector<std::string>& _tokens)
	{
		return _parser->find_longest_matching_command(_tokens);
	}

	void extract_arguments(const std::vector<std::string>& _tokens, size_t _index, CLParsedCommand& _result)
	{
		_parser->extract_arguments(_tokens, _index, _result);
	}

	//-Variables-----------------------------------
protected:
	std::unique_ptr<CLParser> _parser;
};

// handle_dirty_command //=============================================================================
TEST_F(CLParserTests, HandleDirtyCommand_EmptyCommand_ReturnsEmptyCommand)
{
	const auto result = _parser->handle_dirty_command("");
	EXPECT_EQ(result._result_status, ParserResultStatus::EMPTY_COMMAND);
}
TEST_F(CLParserTests, HandleDirtyCommand_WhitespaceOnly_ReturnsEmptyCommand)
{
	const auto result = _parser->handle_dirty_command(" \t ");
	EXPECT_EQ(result._result_status, ParserResultStatus::EMPTY_COMMAND);
}
TEST_F(CLParserTests, HandleDirtyCommand_UnknownCommand_ReturnsInvalidSyntax)
{
	const auto result = _parser->handle_dirty_command("some_unknown_command");
	EXPECT_EQ(result._result_status, ParserResultStatus::INVALID_SYNTAX);
	EXPECT_EQ(result._result_message, "Unknown command");
}
TEST_F(CLParserTests, HandleDirtyCommand_PartiallyMatchingCommand_ReturnsInvalidSyntax)
{
	const auto result = _parser->handle_dirty_command("task");
	EXPECT_EQ(result._result_status, ParserResultStatus::INVALID_SYNTAX);
}
TEST_F(CLParserTests, HandleDirtyCommand_CommandWithArguments_ReturnsSuccess)
{
	const auto result = _parser->handle_dirty_command("task add --title \"My task\"");
	EXPECT_EQ(result._result_status, ParserResultStatus::SUCCESS);
}
TEST_F(CLParserTests, HandleDirtyCommand_CommandWithLongOption_ReturnsSuccess)
{
	const auto result = _parser->handle_dirty_command("task add --title=MyTask");
	EXPECT_EQ(result._result_status, ParserResultStatus::SUCCESS);
}
TEST_F(CLParserTests, HandleDirtyCommand_CommandWithShortOption_ReturnsSuccess)
{
	const auto result = _parser->handle_dirty_command("task add -t MyTask");
	EXPECT_EQ(result._result_status, ParserResultStatus::SUCCESS);
}
TEST_F(CLParserTests, HandleDirtyCommand_CommandWithFlag_ReturnsSuccess)
{
	const auto result = _parser->handle_dirty_command("task add --force");
	EXPECT_EQ(result._result_status, ParserResultStatus::SUCCESS);
}
// find_longest_matching_command //=============================================================================
TEST_F(CLParserTests, FindLongestMatchingCommand_EmptyTokens_ReturnsNullopt)
{
	const std::vector<std::string> tokens;
	const auto result = find_longest_matching_command(tokens);
	EXPECT_FALSE(result.has_value());
}
TEST_F(CLParserTests, FindLongestMatchingCommand_UnknownCommand_ReturnsNullopt)
{
	const std::vector<std::string> tokens { "unknown", "command" };
	const auto result = find_longest_matching_command(tokens);
	EXPECT_FALSE(result.has_value());
}
TEST_F(CLParserTests, FindLongestMatchingCommand_ExistingCommand_ReturnsMatch)
{
	const std::vector<std::string> tokens { "task", "add" };
	const auto result = find_longest_matching_command(tokens);
	ASSERT_TRUE(result.has_value());
	ASSERT_NE(result->first, nullptr);
	EXPECT_EQ(result->second, 2);
}
TEST_F(CLParserTests, FindLongestMatchingCommand_CommandWithArguments_ReturnsCommand)
{
	const std::vector<std::string> tokens { "task", "add", "--title", "Test" };
	const auto result = find_longest_matching_command(tokens);
	ASSERT_TRUE(result.has_value());
	ASSERT_NE(result->first, nullptr);
	EXPECT_EQ(result->second, 2);
}
TEST_F(CLParserTests, FindLongestMatchingCommand_ChoosesLongestMatch)
{
	const std::vector<std::string> tokens { "task", "add", "something" };
	const auto result = find_longest_matching_command(tokens);
	ASSERT_TRUE(result.has_value());
	ASSERT_NE(result->first, nullptr);
	EXPECT_EQ(result->second, 2);
}
// extract_arguments //=============================================================================
TEST_F(CLParserTests, ExtractArguments_NoArguments_LeavesResultEmpty)
{
	const std::vector<std::string> tokens { "task", "add" };
	CLParsedCommand result;
	extract_arguments(tokens, 2, result);
	EXPECT_TRUE(result._options.empty());
	EXPECT_TRUE(result._positional.empty());
}
TEST_F(CLParserTests, ExtractArguments_LongOptionWithValue_ParsesCorrectly)
{
	const std::vector<std::string> tokens { "--title", "MyTask" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("title"), "MyTask");
}
TEST_F(CLParserTests, ExtractArguments_LongOptionWithEquals_ParsesCorrectly)
{
	const std::vector<std::string> tokens { "--title=MyTask" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("title"), "MyTask");
}
TEST_F(CLParserTests, ExtractArguments_LongFlag_StoresEmptyValue)
{
	const std::vector<std::string> tokens { "--force" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("force"), "");
}
TEST_F(CLParserTests, ExtractArguments_ShortOptionWithValue_ParsesCorrectly)
{
	const std::vector<std::string> tokens { "-t", "MyTask" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("t"), "MyTask");
}
TEST_F(CLParserTests, ExtractArguments_ShortFlag_StoresEmptyValue)
{
	const std::vector<std::string> tokens { "-f" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("f"), "");
}
TEST_F(CLParserTests, ExtractArguments_GroupedShortFlags_ParsesAllFlags)
{
	const std::vector<std::string> tokens { "-abc" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 3);
	EXPECT_EQ(result._options.at("a"), "");
	EXPECT_EQ(result._options.at("b"), "");
	EXPECT_EQ(result._options.at("c"), "");
}
TEST_F(CLParserTests, ExtractArguments_PositionalArgument_StoresArgument)
{
	const std::vector<std::string> tokens { "hello" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._positional.size(), 1);
	EXPECT_EQ(result._positional[0], "hello");
}
TEST_F(CLParserTests, ExtractArguments_MultiplePositionalArguments_PreservesOrder)
{
	const std::vector<std::string> tokens { "one", "two", "three" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._positional.size(), 3);
	EXPECT_EQ(result._positional[0], "one");
	EXPECT_EQ(result._positional[1], "two");
	EXPECT_EQ(result._positional[2], "three");
}
TEST_F(CLParserTests, ExtractArguments_MixedArguments_ParsesCorrectly)
{
	const std::vector<std::string> tokens { "positional", "--title", "MyTask", "-f", "--priority=high" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._positional.size(), 1);
	EXPECT_EQ(result._positional[0], "positional");
	ASSERT_EQ(result._options.size(), 3);
	EXPECT_EQ(result._options.at("title"), "MyTask");
	EXPECT_EQ(result._options.at("f"), "");
	EXPECT_EQ(result._options.at("priority"), "high");
}
TEST_F(CLParserTests, ExtractArguments_LongOptionFollowedByAnotherOption_DoesNotConsumeNextOption)
{
	const std::vector<std::string> tokens { "--title", "--force" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 2);
	EXPECT_EQ(result._options.at("title"), "");
	EXPECT_EQ(result._options.at("force"), "");
}
TEST_F(CLParserTests, ExtractArguments_ShortOptionFollowedByAnotherOption_DoesNotConsumeNextOption)
{
	const std::vector<std::string> tokens { "-t", "-f" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 2);
	EXPECT_EQ(result._options.at("t"), "");
	EXPECT_EQ(result._options.at("f"), "");
}
TEST_F(CLParserTests, ExtractArguments_OptionAtEndWithoutValue_StoresEmptyValue)
{
	const std::vector<std::string> tokens { "--title" };
	CLParsedCommand result;
	extract_arguments(tokens, 0, result);
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("title"), "");
}
TEST_F(CLParserTests, ExtractArguments_StartIndex_IsRespected)
{
	const std::vector<std::string> tokens { "task", "add", "--title", "MyTask" };
	CLParsedCommand result;
	extract_arguments(tokens, 2, result);
	ASSERT_TRUE(result._positional.empty());
	ASSERT_EQ(result._options.size(), 1);
	EXPECT_EQ(result._options.at("title"), "MyTask");
}