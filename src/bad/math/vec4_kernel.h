#ifndef BAD_VEC4_KERNEL_H
#define BAD_VEC4_KERNEL_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

void vec4_ker_dot(      f32* bad_restrict dot,
                  const f32* bad_restrict v0,
                  const f32* bad_restrict v1,
                        u32               vec4_count);

void vec4_ker_length_squared(      f32* bad_restrict len_sqr,
                             const f32* bad_restrict v,
                                   u32               vec4_count);

void vec4_ker_length(      f32* bad_restrict len,
                     const f32* bad_restrict v,
                           u32               vec4_count);
                     
void vec4_ker_lerp(      f32* bad_restrict lerp,
                   const f32* bad_restrict v0,
                   const f32* bad_restrict v1,
                   const f32* bad_restrict t,
                         u32               vec4_count);

BAD_NAMESPACE_END

#endif