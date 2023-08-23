#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <spdlog/async.h>
#include <spdlog/fmt/bin_to_hex.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/stopwatch.h>

#define LOG_TRACE(module, ...) SPDLOG_LOGGER_TRACE(spdlog::get(#module), __VA_ARGS__)
#define LOG_DEBUG(module, ...) SPDLOG_LOGGER_DEBUG(spdlog::get(#module), __VA_ARGS__)
#define LOG_INFO(module, ...) SPDLOG_LOGGER_INFO(spdlog::get(#module), __VA_ARGS__)
#define LOG_WARN(module, ...) SPDLOG_LOGGER_WARN(spdlog::get(#module), __VA_ARGS__)
#define LOG_ERROR(module, ...) SPDLOG_LOGGER_ERROR(spdlog::get(#module), __VA_ARGS__)
#define LOG_CRITICAL(module, ...) SPDLOG_LOGGER_CRITICAL(spdlog::get(#module), __VA_ARGS__)

namespace frame {

class Log
{
   public:
    static bool Init(const std::string& process_name);
};

};  // namespace frame