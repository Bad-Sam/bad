#ifndef BAD_VEC4_H
#define BAD_VEC4_H

#include <bad/args.h>
#include <bad/types.h>

#include <bad/common/f32x4.h>

BAD_NAMESPACE_START

typedef f32x4 vec4;

static bad_inline f32 bad_veccall vec4_dot(vec4_vec0 v0, vec4_vec1 v1);
/*
void bad_veccall vec4_dotn(f32* const dot,
                                           const vec4* const bad_restrict v0,
                                           const vec4* const bad_restrict v1,
                                           const u32 n);

void bad_veccall f32_dotn(f32* const dot,
                                          const f32* const bad_restrict v0,
                                          const f32* const bad_restrict v1,
                                          const u32 n);
*/
#include "vec4.inl"

BAD_NAMESPACE_END

#endif