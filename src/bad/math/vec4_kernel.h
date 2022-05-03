#ifndef BAD_VEC4_KERNEL_H
#define BAD_VEC4_KERNEL_H

#include <bad/bad.h>
#include <bad/types.h>
#include <bad/qualifiers.h>

BAD_NAMESPACE_START

void vec4_ker_dot(f32*       bad_restrict dot,
                  const f32* bad_restrict v0,
                  const f32* bad_restrict v1,
                  s32                     vec4_count);

void vec4_ker_length_squared(f32*       bad_restrict len_sqr,
                             const f32* bad_restrict v,
                             s32                     vec4_count);

void vec4_ker_length(f32*       bad_restrict len,
                     const f32* bad_restrict v,
                     s32                     vec4_count);
                     
void vec4_ker_lerp(f32*       bad_restrict lerp,
                   const f32* bad_restrict v0,
                   const f32* bad_restrict v1,
                   const f32* bad_restrict t,
                   s32                     vec4_count);

BAD_NAMESPACE_END

#endif