#ifndef BAD_MATH_TYPES_H
#define BAD_MATH_TYPES_H

#include <bad/bad.h>
#include "simd_types.h"

BAD_NAMESPACE_START

typedef f32x4 vec3;
typedef f32x4 vec4;
typedef f32x4 quat;

typedef struct
{
#if defined(__AVX__)
    union
    {
        f32x8 cols_by_2[2];
        f32x4 cols[4];
    };
#else
    f32x4 cols[4];
#endif
} mat4x4;

BAD_NAMESPACE_END

#endif
