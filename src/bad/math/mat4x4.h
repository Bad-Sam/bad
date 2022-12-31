#ifndef BAD_MAT4X4_H
#define BAD_MAT4X4_H

#include <bad/types/math_types.h>
#include <bad/types/scalar_types.h>
#include <bad/types/simd_types.h>
#include <bad/qualifiers.h>

#if defined(__AVX__)
#   include <bad/common/f32x8.h>
#else
#   include <bad/common/f32x4.h>
#endif

BAD_NAMESPACE_START

static bad_forceinline mat4x4             mat4x4_load(f32* coefs);
static bad_forceinline mat4x4 bad_veccall mat4x4_set_cols(f32x4 col0, f32x4 col1, f32x4 col2, f32x4 col3);

mat4x4 bad_veccall mat4x4_transpose(mat4x4 a);
mat4x4 bad_veccall mat4x4_mul(mat4x4 a, mat4x4 b);

#include "mat4x4.inl"

BAD_NAMESPACE_END

#endif
