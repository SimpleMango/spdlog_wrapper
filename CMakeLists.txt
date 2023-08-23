cmake_minimum_required(VERSION 3.14)

project(framework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -fPIC -pthread)

find_package(Threads)

include_directories(src/frame 3rd)

file(GLOB_RECURSE PROJECT_SOURCES ${PROJECT_SOURCE_DIR}/src/frame/*.cpp)
message("ProjectSources:" ${PROJECT_SOURCES})
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES})

option(BUILD_TEST "Build test" OFF)
if(BUILD_TEST)
  add_subdirectory(test)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
	${OPENSOURCE_INC}
)

message("ARCH_TYPE: " ${ARCH_TYPE})
message("CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
  include(${OPENSOURCE_LIB}/cmake/spdlog/spdlogConfig.cmake)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  include(/usr/local/lib/cmake/spdlog/spdlogConfig.cmake)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    Threads::Threads
    spdlog::spdlog_header_only
    stdc++fs
)