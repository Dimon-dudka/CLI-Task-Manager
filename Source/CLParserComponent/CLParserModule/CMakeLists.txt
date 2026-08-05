set(MODULE_NAME "CLParserModule")

add_library(${MODULE_NAME} SHARED)

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
)

target_link_libraries(${MODULE_NAME}
        PUBLIC CLParserAPI)

target_include_directories(${MODULE_NAME}
        PUBLIC Public
        PRIVATE Private
        PRIVATE Private/Tokenizer
)