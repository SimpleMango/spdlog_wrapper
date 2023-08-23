#include <gtest/gtest.h>

#include "log/Log.h"
#include "thread/ThreadUtils.h"

TEST(LogTest, spdlog)
{
    EXPECT_EQ(true, frame::Log::Init("test"));

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


GTEST_API_ int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}