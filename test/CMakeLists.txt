file(GLOB_RECURSE TEST_SOURCES "*Test.cpp")
message(STATUS "Test sources: ${TEST_SOURCES}")

add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/3rd/Catch2/src)

target_link_libraries(${PROJECT_NAME}_tests
        ${PROJECT_NAME}
        pthread
        Catch2
        Catch2WithMain
        )
