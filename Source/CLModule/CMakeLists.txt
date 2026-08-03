set(MODULE_NAME "CLModule")

add_library(${MODULE_NAME} SHARED)

target_sources(${MODULE_NAME}
        PUBLIC
        FILE_SET cl_module
        TYPE CXX_MODULES FILES
        Public/CLModule.cppm

        PRIVATE
        Private/CLModule.cpp
        # Readers Section
        Private/Reader/ReaderBase.h
        Private/Reader/CLReader/CLReader.h
        Private/Reader/CLReader/CLReader.cpp
        # Tokenizer
        Private/Tokenizer/CLTokenizer.h
        Private/Tokenizer/CLTokenizer.cpp
)

target_include_directories(${MODULE_NAME}
        PUBLIC Public
        PRIVATE Private
        PRIVATE Private/Reader
        PRIVATE Private/Reader/CLReader
        PRIVATE Private/Tokenizer
)