set(MODULE_NAME "CLInputModule")

add_library(${MODULE_NAME} SHARED)

target_sources(${MODULE_NAME}
        PUBLIC
        FILE_SET cl_input_module
        TYPE CXX_MODULES FILES
        Public/CLInputModule.cppm

        PRIVATE
        Private/CLInputModule.cpp
        # Readers Section
        Private/Reader/ReaderBase.h
        Private/Reader/CLReader/CLReader.h
        Private/Reader/CLReader/CLReader.cpp
)

target_link_libraries(CLInputModule
        PRIVATE
        CLParserAPI
)

target_include_directories(${MODULE_NAME}
        PUBLIC Public
        PRIVATE Private
        PRIVATE Private/Reader
        PRIVATE Private/Reader/CLReader
)