#pragma once

#include <time.h>
#include <sys/time.h>

namespace util {

uint64_t get_current_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

}
