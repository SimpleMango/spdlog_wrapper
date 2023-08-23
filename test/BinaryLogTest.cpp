#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#include "log/BinaryLog.h"

constexpr int write_count = 1000'000'000;

TEST(LogTest, BinaryWrite)
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
