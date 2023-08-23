#include "ThreadUtils.h"

#include <csignal>

#include "pthread.h"

bool ThreadUtils::BindThisThread(int cpu)
{
    int cpu_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (cpu >= cpu_count) return false;

    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(3, &cpu_set);
    int ret = pthread_setaffinity_np(pthread_self(),sizeof(cpu_set_t), &cpu_set);
    if (ret != 0) return false;
    return true;
}
