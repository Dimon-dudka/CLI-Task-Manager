find_package(GTest REQUIRED)
if (GTest_FOUND)
    message(STATUS "GTest found: ${GTest_VERSION}")
else ()
    message(FATAL_ERROR "GTest was not found")
endif ()

add_executable(Tests
        test_main.cpp
)

target_link_libraries(Tests
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        CLModule
)

target_include_directories(Tests
        PRIVATE
        ${CMAKE_SOURCE_DIR}/Source/CLModule/Private
        ${CMAKE_SOURCE_DIR}/Source/CLModule/Private/Tokenizer
)

add_subdirectory(CLModuleTests)
