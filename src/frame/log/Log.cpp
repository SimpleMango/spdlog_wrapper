#include "log/Log.h"

#include <filesystem>
#include <iomanip>
#include <pthread.h>

#include "tomlplusplus/toml.hpp"

namespace frame {

bool IsFolderExists(const std::string& folder_path)
{
     return std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path);
}

bool Log::Init(const std::string& process_name)
{
    spdlog::set_pattern("[%C-%m-%d %H:%M:%S.%f][%^%L%$][%t][%s:%#] %v");
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_every(std::chrono::seconds(1));
    spdlog::flush_on(spdlog::level::warn);

    // default_async_q_size
    spdlog::init_thread_pool(spdlog::details::default_async_q_size, 1, []() {
      const char* thread_name = "SpdlogThPool";
      (void)pthread_setname_np(/*pthread_self(),*/ thread_name);
    });

    const std::string conf_path = "conf/log/" + process_name + "_log.toml";
    if (!std::filesystem::exists(conf_path))
    {
        SPDLOG_CRITICAL("conf file is not exist");
        return false;
    }

    const std::string log_dir = "log/" + process_name;

    if (!IsFolderExists(log_dir)) std::filesystem::create_directories(log_dir);

    try
    {
        toml::table config = toml::parse_file(conf_path);
        auto node = config["logger"];
        SPDLOG_INFO("spdlog config is array: {}, is array of tables: {}", node.is_array(), node.is_array_of_tables());
        for (std::size_t i = 0; i < node.as_array()->size(); ++i)
        {
            SPDLOG_INFO("Logger:{},\tLevel:{}", *node[i]["name"].value<std::string>(),
                        *node[i]["level"].value<std::string>());
            std::tm time = spdlog::details::os::localtime();
            std::ostringstream oss;
            oss << std::put_time(&time, "%Y-%m-%d_%H:%M:%S");

            std::string_view log_level = *node[i]["level"].value<std::string_view>();
            std::string module_name = *node[i]["name"].value<std::string>();
            std::string filename = log_dir + "/" + module_name + "_" + oss.str() + ".log";
            auto logger = spdlog::basic_logger_mt<spdlog::async_factory>(module_name, filename);

            spdlog::level::level_enum level = spdlog::level::from_str(log_level.data());
            logger->set_level(level);
        }
    }
    catch (const toml::parse_error& err)
    {
        SPDLOG_ERROR("Toml Parsing failed: {}", err.what());
        return false;
    }
    catch (const std::exception& ex)
    {
        SPDLOG_ERROR("STD exception: {}", ex.what());
        return false;
    }

    SPDLOG_INFO("Log init success");

    return true;
}

};  // namespace frame