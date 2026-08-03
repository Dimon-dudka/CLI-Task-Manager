add_subdirectory(CLModule)

add_executable(${PROJECT_NAME}
        main.cpp
        CLApplication.h
        CLApplication.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        CLModule
)
