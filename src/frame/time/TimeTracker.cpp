#include "time/TimeTracker.h"

#include <iostream>

namespace frame {

TimeTracker::TimeTracker() : last_tick_time_(std::chrono::steady_clock::now()) {}

std::chrono::nanoseconds TimeTracker::Tick()
{
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    std::chrono::nanoseconds diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now - last_tick_time_);
    last_tick_time_ = now;
    return diff;
}

Profiler::Profiler(const char* file, const char* func, const int line, int time_ms)
    : file_(file), func_(func), line_(line), threshold_in_ms_(time_ms)
{
}

Profiler::~Profiler()
{
    auto diff = tracker_.Tick();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
    if (threshold_in_ms_ > 0 && duration_ms.count() < threshold_in_ms_)
    {
        return;
    }

    std::cout << "<Profiler> the execution time of [" << file_ << ":" << func_ << ":" << line_ << "] is "
              << duration_ms.count() << " ms," << (diff - duration_ms).count() << " ns.";
}

}  // namespace frame