set(MODULE_NAME "CLParserAPI")

add_library(${MODULE_NAME} STATIC)

target_sources(${MODULE_NAME}
        PUBLIC
        FILE_SET cl_parser_api
        TYPE CXX_MODULES FILES
        CLParserAPI.cppm
)
