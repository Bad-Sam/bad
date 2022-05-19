#include "vec4_kernel.h"
#include "vec4.h"

#include <bad/debug_checks.h>

BAD_NAMESPACE_START

void vec4_ker_dot(      f32* bad_restrict dot,
                  const f32* bad_restrict a,
                  const f32* bad_restrict b,
                        u32  vec4_count)
{
    bad_assert(dot        != NULL);
    bad_assert(a          != NULL);
    bad_assert(b          != NULL);
    bad_assert(vec4_count != 0u);

    bad_assert_f32xn_aligned(dot);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    const u32 end = (vec4_count << 4);
    for (u32 i = 0u; i < end; i += f32xn_width)
    {
#if defined(__AVX__)
        f32x8 va  = f32x8_load(a + i);
        f32x8 vb  = f32x8_load(b + i);
        f32x8 dot = _mm256_dp_ps(va, vb, 0b11111111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));
#else
        f32x4 va  = f32x4_load(a + i);
        f32x4 vb  = f32x4_load(b + i);
        *dot++ = vec4_dot(va, vb);
#endif
    }
}


void vec4_ker_length_squared(      f32* bad_restrict len_sqr,
                             const f32* bad_restrict a,
                                   u32               vec4_count)
{
    return vec4_ker_dot(len_sqr, a, a, vec4_count);
}


void vec4_ker_length(      f32* bad_restrict len,
                     const f32* bad_restrict a,
                           u32               vec4_count)
{
    const u32 end = (vec4_count << 4);
    for (u32 i = 0u; i < end; i += f32xn_width)
    {

#if defined(__AVX__)
        f32x/ va = f32x/_load(a + i);
        f32x8 dot = _mm256_dp_ps(va, va, 0b11111111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
              mix = f32x8_sqrt(mix);
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));
#else
        f32x4 va = f32x4_load(a + i);
        *len++ = vec4_length(va);
#endif
    }
}


void vec4_ker_lerp(      f32* bad_restrict lerp,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                   const f32* bad_restrict t,
                         u32               vec4_count)
{
    bad_assert(lerp       != NULL);
    bad_assert(a          != NULL);
    bad_assert(b          != NULL);
    bad_assert(t          != NULL);
    bad_assert(vec4_count != 0u);
    bad_assert_f32xn_aligned(lerp);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);
    bad_assert_f32xn_aligned(t);

    const u32   end = (vec4_count << 4);

#if defined(__AVX__)
    const f32x8 one = f32x8_one();
#endif

    for (u32 i = 0u; i < end; i += f32xn_width)
    {
#if defined(__AVX__)
        f32x8 va = f32x8_load(a + i);
        f32x8 vb = f32x8_load(b + i);
        f32x8 vt = _mm256_set_m128(f32x4_set_all(t[0]), f32x4_set_all(t[1]));

        f32x8 one_min_t = f32x8_sub(one, vt);

        f32x8 lerped = f32x8_mul_add(one_min_t, va, f32x8_mul(vt, vb));

        f32x8_store(res, lerped);
#else
        f32x4 va     = f32x4_load(a + i);
        f32x4 vb     = f32x4_load(b + i);

        f32x4 lerped = vec4_lerp(va, vb, *t++);

        f32x4_store(lerp, lerped);
#endif
    }
}

BAD_NAMESPACE_END