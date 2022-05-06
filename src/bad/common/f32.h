#ifndef BAD_F32_H
#define BAD_F32_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

static bad_forceinline f32 f32_blend(f32 a, f32 b, u32 m);
static bad_forceinline u32 f32_as_u32(f32 a);

#include "f32.inl"

BAD_NAMESPACE_END

#endif