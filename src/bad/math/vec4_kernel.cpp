#include "vec4_kernel.h"

#include <bad/debug.h>
#include "vec4.h"

BAD_NAMESPACE_START

void vec4_ker_dot(f32*       bad_restrict dot,
                  const f32* bad_restrict v0,
                  const f32* bad_restrict v1,
                  s32                     vec4_count)
{
    bad_assert(dot != NULL);
    bad_assert(v0  != NULL);
    bad_assert(v1  != NULL);

    bad_assert_sse_aligned(dot);
    bad_assert_sse_aligned(v0);
    bad_assert_sse_aligned(v1);

    const s32 end = vec4_count * 4;
    for (s32 i = 0; i < end; i += 4)
    {
        f32x4 a = f32x4_load(v0 + i);
        f32x4 b = f32x4_load(v1 + i);

        *dot++ = vec4_dot(a, b);
    }
}


void vec4_ker_length_squared(f32*       bad_restrict len_sqr,
                             const f32* bad_restrict v,
                             s32                     vec4_count)
{
    bad_assert(len_sqr != NULL);
    bad_assert(v       != NULL);

    bad_assert_sse_aligned(len_sqr);
    bad_assert_sse_aligned(v);

    const s32 end = vec4_count * 4;
    for (s32 i = 0; i < end; i += 4)
    {
        f32x4 a  = f32x4_load(v + i);
        *len_sqr = vec4_length_squared(a);
        len_sqr++;
    }
}


void vec4_ker_length(f32*       bad_restrict len,
                     const f32* bad_restrict v,
                     s32                     vec4_count)
{
    bad_assert(len != NULL);
    bad_assert(v   != NULL);

    bad_assert_sse_aligned(len);
    bad_assert_sse_aligned(v);

    const s32 end = vec4_count * 4;
    for (s32 i = 0; i < end; i += 4)
    {
        f32x4 a = f32x4_load(v + i);
        *len++  = vec4_length(a);
    }
}


void vec4_ker_lerp(f32*       bad_restrict lerp,
                   const f32* bad_restrict v0,
                   const f32* bad_restrict v1,
                   const f32* bad_restrict t,
                   s32                     vec4_count)
{
    bad_assert(lerp != NULL);
    bad_assert(v0   != NULL);
    bad_assert(v1   != NULL);
    bad_assert(t    != NULL);

    bad_assert_sse_aligned(lerp);
    bad_assert_sse_aligned(v0);
    bad_assert_sse_aligned(v1);
    bad_assert_sse_aligned(t);

    const s32 end = vec4_count * 4;
    for (s32 i = 0; i < end; i += 4)
    {
        f32x4 a = f32x4_load(v0 + i);
        f32x4 b = f32x4_load(v1 + i);

        f32x4_store(lerp + i, vec4_lerp(a, b, t[i]));
    }
}

BAD_NAMESPACE_END