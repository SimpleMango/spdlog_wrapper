cmake_minimum_required(VERSION 3.25)

project(spdlog_wrapper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -fPIC -pthread)

find_package(Threads)

include_directories(src/frame
        3rd
        3rd/spdlog/include
        )

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/frame/*.cpp)
message("ProjectSources:" ${PROJECT_SOURCES})
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Threads::Threads
    spdlog::spdlog_header_only
)

add_subdirectory(3rd/spdlog)
add_subdirectory(3rd/Catch2)
add_subdirectory(test)
