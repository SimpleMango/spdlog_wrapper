#pragma once

#include <chrono>

/**
 * ROBO_PROFILER 用于对函数进行profiler，会以DEBUG级别输出Profiler信息到日志
 */
#define ROBO_PROFILER robokit::frame::Profiler __robokit_profiler_##__LINE__##__(__FILE__, __FUNCTION__, __LINE__)

/**
 * ROBO_PROFILER 用于对函数进行profiler，在大于指定的time_ms时,会以指定log severity级别输出Profiler信息到日志
 */
#define ROBO_PROFILER_MS(time_ms)                                                                                      \
    robokit::frame::Profiler __robokit_profiler_##__LINE__##__(__FILE__, __FUNCTION__, __LINE__, time_ms)

namespace frame {

/**
 * TimeTracker是一个计时器，类似体育竞赛裁判手上的秒表。
 * TimerTracker会维护最后一次执行Tick的时间点（初始时记录构造该实例的时间点） *
 * 使用Tick函数可以获取当前时间和上一次Tick的时间间隔，并且记录最后一次Tick时间
 */
class TimeTracker
{
   public:
    TimeTracker();
    ~TimeTracker() = default;

    /**
     * 进行一次计时操作
     * @return 本次计时操作与上一次计时操作的时间间隔（纳秒）
     */
    std::chrono::nanoseconds Tick();

   private:
    // 最后一次计时操作的时间
    std::chrono::time_point<std::chrono::steady_clock> last_tick_time_;
};

class Profiler
{
   public:
    explicit Profiler(const char* file, const char* func, int line, int threshold_in_ms = 0);

    ~Profiler();

   private:
    // 时间追踪器
    TimeTracker tracker_;
    // 进行profile的文件名
    const char* const file_;
    // 进行profiler的函数名
    const char* const func_;
    // 进行profile的文件行数
    const int line_;
    // 计时时间
    int threshold_in_ms_ = 0;
};

}  // namespace frame