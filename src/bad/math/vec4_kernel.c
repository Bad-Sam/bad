#include "vec4_kernel.h"

#include "f32xn_calc.h"
#include "vec4.h"

#include <bad/debug_checks.h>

BAD_NAMESPACE_START

void vec4_ker_dot(      f32* bad_restrict res,
                  const f32* bad_restrict a,
                  const f32* bad_restrict b,
                        u32               vec4_count)
{
    bad_debug_check(res        != NULL);
    bad_debug_check(a          != NULL);
    bad_debug_check(b          != NULL);
    bad_debug_check(vec4_count != 0u);
    bad_debug_check_aligned(a, f32xn);
    bad_debug_check_aligned(b, f32xn);

    const u32 end = vec4_count * 4u;
    for (u32 i = 0u; i < end; i += f32xn_width)
    {
#if (f32xn_width == 8u)
        f32x8 va  = f32x8_load(a + i);
        f32x8 vb  = f32x8_load(b + i);
        f32x8 dot = _mm256_dp_ps(va, vb, 0b11111111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));

        res += 2u;
#else
        f32x4 va  = f32x4_load(a + i);
        f32x4 vb  = f32x4_load(b + i);
        *res++    = vec4_dot(va, vb);
#endif
    }
}


void vec4_ker_length_squared(      f32* bad_restrict res,
                             const f32* bad_restrict a,
                                   u32               vec4_count)
{
    return vec4_ker_dot(res, a, a, vec4_count);
}


void vec4_ker_length(      f32* bad_restrict res,
                     const f32* bad_restrict a,
                           u32               vec4_count)
{
    bad_debug_check(res        != NULL);
    bad_debug_check(a          != NULL);
    bad_debug_check(vec4_count != 0u);
    bad_debug_check_aligned(res, f32xn);
    bad_debug_check_aligned(a,   f32xn);

    const u32 end = vec4_count * 4u;
    for (u32 i = 0u; i < end; i += f32xn_width)
    {

#if (f32xn_width == 8u)
        f32x8 va  = f32x8_load(a + i);
        f32x8 dot = _mm256_dp_ps(va, va, 0b11111111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
              mix = f32x8_sqrt(mix);
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));
        res += 2u;
#else
        f32x4 va = f32x4_load(a + i);
        *res++ = vec4_length(va);
#endif
    }
}


void vec4_ker_lerp(      f32* bad_restrict res,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                   const f32* bad_restrict t,
                         u32               vec4_count)
{
    bad_debug_check(res        != NULL);
    bad_debug_check(a          != NULL);
    bad_debug_check(b          != NULL);
    bad_debug_check(t          != NULL);
    bad_debug_check(vec4_count != 0u);
    bad_debug_check_aligned(res, f32xn);
    bad_debug_check_aligned(a,   f32xn);
    bad_debug_check_aligned(b,   f32xn);

#if (f32xn_width == 8u)
    const f32x8 one = f32x8_one();
#endif

    const u32 end = vec4_count * 4u;
    for (u32 i = 0u; i < end; i += f32xn_width)
    {
#if (f32xn_width == 8u)
        f32x8 va = f32x8_load(a + i);
        f32x8 vb = f32x8_load(b + i);
        f32x8 vt = _mm256_set_m128(f32x4_set_all(t[0]), f32x4_set_all(t[1]));

        f32x8 one_min_t = f32x8_sub(one, vt);

        f32x8 lerped = f32x8_mul_add(one_min_t, va, f32x8_mul(vt, vb));

        f32x8_store(res + i, lerped);

        t += 2u;
#else
        f32x4 va     = f32x4_load(a + i);
        f32x4 vb     = f32x4_load(b + i);

        f32x4 lerped = vec4_lerp(va, vb, *t++);

        f32x4_store(res + i, lerped);
#endif
    }
}

BAD_NAMESPACE_END
