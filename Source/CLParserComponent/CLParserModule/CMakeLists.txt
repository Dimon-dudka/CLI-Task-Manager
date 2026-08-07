set(MODULE_NAME "CLParserModule")

add_library(${MODULE_NAME} SHARED)

# ============================================================
# Parser API
# ============================================================

add_library(CLParserAPI INTERFACE)

target_include_directories(CLParserAPI
        INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
)

# ============================================================
# Parser Module
# ============================================================

target_sources(${MODULE_NAME}
        PUBLIC
        FILE_SET cl_parser_module
        TYPE CXX_MODULES FILES
        Public/CLParserModule.cppm

        PRIVATE
        Private/CLParserModule.cpp
        # Tokenizer
        Private/Tokenizer/CLTokenizer.h
        Private/Tokenizer/CLTokenizer.cpp
        # Parser
        Public/ParserBase.h
        Private/Parser/CLParser.h
        Private/Parser/CLParser.cpp
        # CommandRegistry
        Private/CommandRegistry/Registry/CommandRegistry.h
        Private/CommandRegistry/Registry/CommandRegistry.cpp
        # Commands
        Private/CommandRegistry/Contract/CommandArguments.h
        Private/CommandRegistry/Commands/BaseCommand.h
        Private/CommandRegistry/Commands/AddCommand/AddCommand.h
        Private/CommandRegistry/Commands/AddCommand/AddCommand.cpp
)

target_link_libraries(${MODULE_NAME}
        PUBLIC
        CLParserAPI
)

target_include_directories(${MODULE_NAME}
        PUBLIC Public
        PRIVATE Private
        PRIVATE Private/Tokenizer
        PRIVATE Private/Parser
        PRIVATE Private/CommandRegistry/Registry
        PRIVATE Private/CommandRegistry/Contract
        PRIVATE Private/CommandRegistry/Commands
        PRIVATE Private/CommandRegistry/Commands/AddCommand
        PRIVATE Private/CommandRegistry/Commands/DeleteCommand
        PRIVATE Private/CommandRegistry/Commands/ListCommand
)