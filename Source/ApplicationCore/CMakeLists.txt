set(MODULE_NAME "ApplicationCore")

add_library(${MODULE_NAME} SHARED)

add_subdirectory(Public/ApplicationAPI)
add_subdirectory(Public/ApplicationCoreModule)

target_include_directories(${MODULE_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Public

        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)