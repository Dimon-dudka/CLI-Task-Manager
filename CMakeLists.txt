cmake_minimum_required(VERSION 3.27)

project(CLI-Task-Manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Project build variables
set(CMAKE_BUILD_LOG_PREFIX "[${PROJECT_NAME}]")
set(ENABLE_TESTS TRUE)

if (ENABLE_TESTS)
    message(DEBUG "${CMAKE_BUILD_LOG_PREFIX} ENABLE_TESTS = ${ENABLE_TESTS}, using testing environment")
    add_compile_definitions(ENABLE_TESTS)
endif ()

add_subdirectory(Source)

if (ENABLE_TESTS)
    set(TESTS_FOLDER Tests)

    enable_testing()
    add_subdirectory(${TESTS_FOLDER})
endif ()