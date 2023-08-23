#include "BinaryLog.h"

#include <spdlog/spdlog.h>

namespace frame {

BinaryLog::~BinaryLog()
{
    if (file_) fclose(file_);
}

bool BinaryLog::Init(const char* file_name)
{
    char folder_path[256];
    snprintf(folder_path, sizeof(folder_path), "%s", file_name);
    char* slash = strrchr(folder_path, '/');
    if (slash != nullptr)
    {
        *slash = '\0';
        mkdir(folder_path, 0777);
    }

    file_ = fopen(file_name, "a+");
    if (!file_)
    {
        SPDLOG_ERROR("open file fail, {}", file_name);
        return false;
    }
    SPDLOG_INFO("open file {} suc", file_name);
    return true;
}

bool BinaryLog::Write(const void* data, size_t data_size)
{
    if (file_ == nullptr) return false;
    size_t ret = fwrite(data, data_size, 1, file_);
    return ret > 0;
}

}  // namespace frame