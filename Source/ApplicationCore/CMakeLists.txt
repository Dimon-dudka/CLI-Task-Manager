set(MODULE_NAME "ApplicationCore")

add_library(${MODULE_NAME} SHARED)

target_sources(${MODULE_NAME}
        PUBLIC
        FILE_SET cl_module
        TYPE CXX_MODULES FILES
        Public/ApplicationCore.cppm

        PRIVATE
        Private/ApplicationCore.cpp
)

target_include_directories(${MODULE_NAME}
        PUBLIC Public
        PRIVATE Private
)