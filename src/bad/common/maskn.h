#ifndef BAD_MASKXN_H
#define BAD_MASKXN_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// maskn is the widest available vector
#if defined(BAD_FORCE_WIDEST_VEC) || defined(BAD_FORCE_8WAY_VEC)
    static const s32 maskn_width = 8;
    typedef maskn mask256;
#elif defined(BAD_FORCE_4WAY_VEC)
    static const s32 maskn_width = 4;
    typedef maskn mask128;
#elif defined(BAD_FORCE_TINIEST_VEC) || defined(BAD_FORCE_1WAY_VEC)
    static const s32 maskn_width = 1;
    typedef maskn f32;
#else // By default, use the widest available SIMD intrinsics type
#   if defined(__AVX__)
        static const s32 maskn_width = 8;
        typedef maskn mask256;
#   elif defined(__SSE__) || defined(__ARM_NEON_FP)
        static const s32 maskn_width = 4;
        typedef maskn mask128;
#   else
        static const s32 maskn_width = 1;
        typedef maskn f32;
#   endif
#endif

BAD_NAMESPACE_END

#endif