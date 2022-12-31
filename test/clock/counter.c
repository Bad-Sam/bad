#include "counter.h"

#include <bad/detect/os.h>

#if defined(BAD_LINUX)
#   include <time.h>
#elif defined(BAD_WINDOWS)
#   include <windows.h>
#endif

BAD_NAMESPACE_START

s64 get_perf_counter()
{
#if defined(BAD_LINUX)
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    return ts.tv_nsec * 1000;
#elif defined(BAD_WINDOWS)
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    return counter.QuadPart;
#endif
}


s64 get_tsc()
{
#if defined(BAD_LINUX)
    return 0ll;
#elif defined(BAD_WINDOWS)
    return __rdtsc();
#endif
}

BAD_NAMESPACE_END
