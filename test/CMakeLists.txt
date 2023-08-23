find_package(GTest REQUIRED)
file(GLOB_RECURSE TEST_SOURCES "*Test.cpp")
message(STATUS "Test sources: ${TEST_SOURCES}")
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests
        ${GTEST_LIBRARIES}
        ${PROJECT_NAME}
        pthread)