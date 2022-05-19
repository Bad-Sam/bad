#ifndef BAD_COUNTER_H
#define BAD_COUNTER_H

#include <bad/bad.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

s64 get_perf_counter();
s64 get_tsc();

BAD_NAMESPACE_END

#endif