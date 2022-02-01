#ifndef BAD_F32XN_H
#define BAD_F32XN_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// f32xn is the widest available vector
#if defined(BAD_FORCE_WIDEST_VEC) || defined(BAD_FORCE_8WAY_VEC)
    static const s32 f32xn_width = 8;
    typedef f32xn f32x8;
#elif defined(BAD_FORCE_4WAY_VEC)
    static const s32 f32xn_width = 4;
    typedef f32xn f32x4;
#elif defined(BAD_FORCE_TINIEST_VEC) || defined(BAD_FORCE_1WAY_VEC)
    static const s32 f32xn_width = 1;
    typedef f32xn f32;
#else // By default, use the widest available SIMD intrinsics type
#   if defined(__AVX__)
        static const s32 f32xn_width = 8;
        typedef f32xn f32x8;
#   elif defined(__SSE__) || defined(__ARM_NEON_FP)
        static const s32 f32xn_width = 4;
        typedef f32xn f32x4;
#   else
        static const s32 f32xn_width = 1;
        typedef f32xn f32;
#   endif
#endif

BAD_NAMESPACE_END

#endif