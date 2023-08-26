#include "catch2/catch_test_macros.hpp"
#include "log/BinaryLog.h"
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"

constexpr long write_count = 1'000'000;

TEST_CASE("BinaryLogTest", "[BinaryWrite]")
{
    frame::BinaryLog bl;
    bl.Init("log/log.bin");
    spdlog::stopwatch ws;
    for (int i = 0; i < write_count; ++i)
    {
        bl.Write( &i, sizeof(i));
    }
    SPDLOG_INFO("ws: {} ", ws);
}
