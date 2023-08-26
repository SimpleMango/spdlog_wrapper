#include "catch2/catch_test_macros.hpp"
#include "catch2/benchmark/catch_benchmark.hpp"
#include "log/Log.h"
#include "thread/ThreadUtils.h"

TEST_CASE("LogTest", "[spdlog]")
{
    REQUIRE(true == frame::Log::Init("test"));

    ThreadUtils::BindThisThread(3);

    int i = 0;
    while(i++ < 10)
    {
        LOG_TRACE(module_1, "this is a line {}", i);
        LOG_DEBUG(module_1, "this is a line {}", i);
        LOG_INFO(module_1, "this is a line {}", i);
        LOG_WARN(module_2, "this is a line {}", i);
        LOG_ERROR(module_2, "this is a line {}", i);
        LOG_CRITICAL(module_2, "this is a line {}", i);
    }
}

TEST_CASE("LogBench", "![spdlog]")
{
    REQUIRE(true == frame::Log::Init("test"));

    int i = 0;
    BENCHMARK("mango"){
       LOG_CRITICAL(module_2, "this is a line {}", i++);
    };
}
