#include "vec3_kernel.h"

#include "f32xn_calc.h"
#include "vec3.h"

BAD_NAMESPACE_START

#if (f32xn_width == 8u) && defined(__AVX__)
#define ker_loop_offset 6u
#else
#define ker_loop_offset 3u
#endif

void vec3_ker_dot(      f32* bad_restrict res,
                  const f32* bad_restrict a,
                  const f32* bad_restrict b,
                        u32               vec3_count)
{
    bad_debug_check(res        != NULL);
    bad_debug_check(a          != NULL);
    bad_debug_check(b          != NULL);
    bad_debug_check(vec3_count != 0u);

    bad_debug_check_aligned(a, f32x4);
    bad_debug_check_aligned(b, f32x4);

    const u32 end = vec3_count * 3u;
    for (u32 i = 0u; i < end; i += ker_loop_offset)
    {
#if (f32xn_width == 8u) && defined(__AVX__)
        const f32* a_i = a + i;
        const f32* b_i = b + i;
        
        f32x4 lo = f32x4_load(a_i);
        f32x4 hi = f32x4_loadu(a_i + 3u);
        f32x8 va = _mm256_set_m128(hi, lo);

        lo       = f32x4_load(b_i);
        hi       = f32x4_loadu(b_i + 3u);
        f32x8 vb = _mm256_set_m128(hi, lo);

        f32x8 dot = _mm256_dp_ps(va, vb, 0b01110111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));

        res += 2u;
#else
        f32x4 va  = f32x4_load(a + i);
        f32x4 vb  = f32x4_load(b + i);
        *res++    = vec3_dot(va, vb);
#endif
    }
}


void vec3_ker_length_squared(      f32* bad_restrict res,
                             const f32* bad_restrict a,
                                   u32               vec3_count)
{
    return vec3_ker_dot(res, a, a, vec3_count);
}


void vec3_ker_length(      f32* bad_restrict res,
                     const f32* bad_restrict a,
                           u32               vec3_count)
{
    bad_debug_check(res        != NULL);
    bad_debug_check(a          != NULL);
    bad_debug_check(vec3_count != 0u);
    bad_debug_check_aligned(a, f32x4);

    const u32 end = vec3_count * 3u;
    for (u32 i = 0u; i < end; i += ker_loop_offset)
    {
#if (f32xn_width == 8u) && defined(__AVX__)
        const f32* a_i = a + i;
        
        f32x4 lo = f32x4_load(a_i);
        f32x4 hi = f32x4_loadu(a_i + 3u);
        f32x8 va = _mm256_set_m128(hi, lo);

        f32x8 dot = _mm256_dp_ps(va, va, 0b01110111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));
#else
        f32x4 va   = f32x4_load(a + i);
        f32x4 unit = vec3_unit(va);
        f32x4_store(res + i, unit);
#endif
    }
}


void vec3_ker_unit(      f32* bad_restrict res,
                   const f32* bad_restrict a,
                         u32               vec3_count)
{
    bad_debug_check(res        != NULL);
    bad_debug_check(a          != NULL);
    bad_debug_check(vec3_count != 0u);

    const u32 end = vec3_count * 3u;

    for (u32 i = 0u; i < end; i += ker_loop_offset)
    {
#if ker_loop_offset == 6u
        const f32* a_i = a + i;
        
        f32x4 lo = f32x4_load(a_i);
        f32x4 hi = f32x4_loadu(a_i + 3u);
        f32x8 va = _mm256_set_m128(hi, lo);

        f32x8 dot = _mm256_dp_ps(va, va, 0b01110111);
        f32x4 ext = _mm256_extractf128_ps(dot, 1);

        f32x8 mix = _mm256_unpacklo_ps(dot, _mm256_castps128_ps256(ext));
              mix = f32x8_sqrt(mix);
        _mm_storel_pi((__m64*)res, _mm256_castps256_ps128(mix));

        res += 2u;
#else
        f32x4 va   = f32x4_load(a + i);
        f32x4 unit = vec3_unit(va);

        f32x4_store(res + i, unit);
#endif   
    }
}

/*
void vec3_ker_cross(      f32* bad_restrict res,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               vec3_count)
{

}


void vec3_ker_project_on(      f32* bad_restrict res,
                         const f32* bad_restrict v,
                         const f32* bad_restrict axis,
                               u32               vec3_count)
{

}


void vec3_ker_project_on_unit(      f32* bad_restrict res,
                              const f32* bad_restrict v,
                              const f32* bad_restrict axis,
                                    u32               vec3_count)
{

}


void vec3_ker_reflect(      f32* bad_restrict res,
                      const f32* bad_restrict v,
                      const f32* bad_restrict unit_normal,
                            u32               vec3_count)
{
    (void)res;
}


void vec3_ker_rot_around_axis(      f32* bad_restrict res,
                              const f32* bad_restrict v,
                              const f32* bad_restrict unit_axis,
                              const f32* bad_restrict angle,
                                    u32               vec3_count)
{
    (void)
}


void vec3_ker_lerp(      f32* bad_restrict res,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                   const f32* bad_restrict t,
                         u32               vec3_count)
{

}
*/

BAD_NAMESPACE_END
