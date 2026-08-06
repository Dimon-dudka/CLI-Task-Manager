#include "CLTokenizer.h"
#include <gtest/gtest.h>

class CLTokenizerTests : public testing::Test
{
	//-Lifecycle-----------------------------------
	//-Methods-------------------------------------
protected:
	virtual void SetUp() override
	{
		Test::SetUp();
		_tokenizer = std::make_unique<CLTokenizer>();
	}
	virtual void TearDown() override
	{
		Test::TearDown();
	}

	//-Variables-----------------------------------
protected:
	std::unique_ptr<CLTokenizer> _tokenizer;
};

TEST_F(CLTokenizerTests, EmptyInputReturnsEmptyVector)
{
	const auto result = _tokenizer->tokenize("");
	EXPECT_TRUE(result.empty());
}

TEST_F(CLTokenizerTests, SingleToken)
{
	const auto result = _tokenizer->tokenize("add");
	ASSERT_EQ(result.size(), 1);
	EXPECT_EQ(result[0], "add");
}

TEST_F(CLTokenizerTests, MultipleTokensSeparatedBySpaces)
{
	const auto result = _tokenizer->tokenize("add task");
	ASSERT_EQ(result.size(), 2);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "task");
}

TEST_F(CLTokenizerTests, MultipleSpacesAreIgnored)
{
	const auto result = _tokenizer->tokenize("add task test");
	ASSERT_EQ(result.size(), 3);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "task");
	EXPECT_EQ(result[2], "test");
}

TEST_F(CLTokenizerTests, LeadingAndTrailingSpacesAreIgnored)
{
	const auto result = _tokenizer->tokenize(" add task ");
	ASSERT_EQ(result.size(), 2);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "task");
}

TEST_F(CLTokenizerTests, QuotedTextIsSingleToken)
{
	const auto result = _tokenizer->tokenize("add task \"Hello Task\"");
	ASSERT_EQ(result.size(), 3);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "task");
	EXPECT_EQ(result[2], "Hello Task");
}

TEST_F(CLTokenizerTests, QuotedTextWithCommandArgument)
{
	const auto result = _tokenizer->tokenize("add task \"Hello Task\" --j");
	ASSERT_EQ(result.size(), 4);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "task");
	EXPECT_EQ(result[2], "Hello Task");
	EXPECT_EQ(result[3], "--j");
}

TEST_F(CLTokenizerTests, QuotedTextContainingMultipleSpaces)
{
	const auto result = _tokenizer->tokenize("add task \"Hello World Task\" --j");
	ASSERT_EQ(result.size(), 4);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "task");
	EXPECT_EQ(result[2], "Hello World Task");
	EXPECT_EQ(result[3], "--j");
}

TEST_F(CLTokenizerTests, MultipleQuotedArguments)
{
	const auto result = _tokenizer->tokenize("add \"Hello World\" \"Another Task\" --j");
	ASSERT_EQ(result.size(), 4);
	EXPECT_EQ(result[0], "add");
	EXPECT_EQ(result[1], "Hello World");
	EXPECT_EQ(result[2], "Another Task");
	EXPECT_EQ(result[3], "--j");
}