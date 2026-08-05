add_subdirectory(CLParserComponent/CLParserAPI)
add_subdirectory(CLParserComponent/CLParserModule)
add_subdirectory(CLInputModule)

# add_subdirectory(ApplicationCore)

add_executable(${PROJECT_NAME}
        main.cpp
        CLApplication.h
        CLApplication.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        CLInputModule
        CLParserModule
)