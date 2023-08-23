#pragma once

#include <cstdio>

namespace frame {

class BinaryLog
{
   public:
    BinaryLog() = default;
    ~BinaryLog();
    bool Init(const char* file_name);
    bool Write(const void* data, size_t data_size);

   private:
    FILE* file_{nullptr};
};

};  // namespace frame