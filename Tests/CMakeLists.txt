find_package(GTest REQUIRED)
if (GTest_FOUND)
    message(STATUS "GTest found: ${GTest_VERSION}")
else ()
    message(FATAL_ERROR "GTest was not found")
endif ()

set(TESTS_MODULE_NAME "Tests_Module")

add_executable(${TESTS_MODULE_NAME})

target_sources(${TESTS_MODULE_NAME} PRIVATE
        test_main.cpp
)

#target_sources(${TESTS_MODULE_NAME} test_main.cpp)

target_link_libraries(${TESTS_MODULE_NAME}
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        CLParserModule
)

target_include_directories(${TESTS_MODULE_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/Source/CLParserComponent/CLParserModule/Private
        ${CMAKE_SOURCE_DIR}/Source/CLParserComponent/CLParserModule/Private/Tokenizer
)

add_subdirectory(CLParserComponentTests)
