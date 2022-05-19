#include "calc_kernel.h"

#include <bad/debug_checks.h>
#include <bad/common/maskn.h>
#include <bad/math/constants.h>
#include <bad/math/f32xn_calc.h>

BAD_NAMESPACE_START

// =========== Arithmetic ===========
void f32_add_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va = f32xn_load(a + i);
        f32xn vb = f32xn_load(b + i);
        
        f32xn res = f32xn_add(va, vb);

        f32xn_store(dst + i, res);
    }
}

void f32_sub_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va = f32xn_load(a + i);
        f32xn vb = f32xn_load(b + i);
        
        f32xn res = f32xn_sub(va, vb);

        f32xn_store(dst + i, res);
    }
}

                               
void f32_mul_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va = f32xn_load(a + i);
        f32xn vb = f32xn_load(b + i);
        
        f32xn res = f32xn_mul(va, vb);

        f32xn_store(dst + i, res);
    }
}


void f32_div_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va = f32xn_load(a + i);
        f32xn vb = f32xn_load(b + i);
        
        f32xn res = f32xn_div(va, vb);

        f32xn_store(dst + i, res);
    }
}


// ====== Advanced arithmetic =======
void f32_rcp_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        
        f32xn res = f32xn_rcp(vsrc);

        f32xn_store(dst + i, res);
    }
}

void f32_sqrt_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        
        f32xn res = f32xn_sqrt(vsrc);

        f32xn_store(dst + i, res);
    }
}

void f32_rsqrt_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        
        f32xn res = f32xn_rsqrt(vsrc);

        f32xn_store(dst + i, res);
    }
}
       
void f32_min_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va = f32xn_load(a + i);
        f32xn vb = f32xn_load(b + i);
        
        f32xn res = f32xn_min(va, vb);

        f32xn_store(dst + i, res);
    }
}

void f32_max_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va = f32xn_load(a + i);
        f32xn vb = f32xn_load(b + i);
        
        f32xn res = f32xn_max(va, vb);

        f32xn_store(dst + i, res);
    }
}

void f32_abs_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn value32_mask = maskn_value32();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);

        maskn vsrc_bits = f32xn_as_maskn(vsrc);
        maskn res_bits  = maskn_and(vsrc_bits, value32_mask);
        f32xn res       = maskn_as_f32xn(res_bits);

        f32xn_store(dst + i, res);
    }
}


void f32_sign_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn highbit32_mask = maskn_highbit32();
    const maskn vone           = f32xn_as_maskn(f32xn_one());

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);

        maskn vsrc_bits = f32xn_as_maskn(vsrc);
        maskn sign_bit  = maskn_and(vsrc_bits, highbit32_mask);
        maskn res_bits  = maskn_or(vone, sign_bit);
        f32xn res       = maskn_as_f32xn(res_bits);

        f32xn_store(dst + i, res);
    }
}

       
void f32_neg_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn highbit32_mask = maskn_highbit32();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);

        maskn vsrc_bits = f32xn_as_maskn(vsrc);
        maskn res_bits  = maskn_xor(vsrc_bits, highbit32_mask);
        f32xn res       = maskn_as_f32xn(res_bits);

        f32xn_store(dst + i, res);
    }
}

       
void f32_frac_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_frac(vsrc);

        f32xn_store(dst + i, res);
    }
}
       
void f32_mod_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        f32xn res = f32xn_mod(va, vb);

        f32xn_store(dst + i, res);
    }
}


void f32_trunc_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_trunc(vsrc);

        f32xn_store(dst + i, res);
    }
}
       

void f32_round_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_round(vsrc);

        f32xn_store(dst + i, res);
    }
}


void f32_floor_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_floor(vsrc);

        f32xn_store(dst + i, res);
    }
}


void f32_ceil_kernel(       f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_ceil(vsrc);

        f32xn_store(dst + i, res);
    }
}


void f32_clamp_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict a,
                      const f32* bad_restrict min,
                      const f32* bad_restrict max,
                            u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(min      != NULL);
    bad_assert(max      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(min);
    bad_assert_f32xn_aligned(max);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va   = f32xn_load(a   + i);
        f32xn vmin = f32xn_load(min + i);
        f32xn vmax = f32xn_load(max + i);

        f32xn res  = f32xn_clamp(va, vmin, vmax);

        f32xn_store(dst + i, res);
    }
}


void f32_lerp_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict a,
                     const f32* bad_restrict b,
                     const f32* bad_restrict t,
                    u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(t        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);
    bad_assert_f32xn_aligned(t);

    const f32xn vone = f32xn_one();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va        = f32xn_load(a + i);
        f32xn vb        = f32xn_load(b + i);
        f32xn vt        = f32xn_load(t + i);
        f32xn one_min_t = f32xn_sub(vone, vt);

        f32xn res = f32xn_mul(vt, vb);
              res = f32xn_mul_add(one_min_t, va, res);

        f32xn_store(dst + i, res);
    }
}


void f32_copysign_kernel(      f32* bad_restrict dst,
                         const f32* bad_restrict a,
                         const f32* bad_restrict reference_sign,
                               u32               max_size)
{
    bad_assert(dst            != NULL);
    bad_assert(a              != NULL);
    bad_assert(reference_sign != NULL);
    bad_assert(max_size       != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(reference_sign);

    const maskn value32_mask = maskn_set_all(0x7FFFFFFF);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va              = f32xn_load(a              + i);
        f32xn vreference_sign = f32xn_load(reference_sign + i);

        maskn a_bits    = f32xn_as_maskn(va);
        maskn sign_bits = f32xn_as_maskn(vreference_sign);
              sign_bits = maskn_and_not(sign_bits, value32_mask);
        maskn a_value   = maskn_and(a_bits, value32_mask);
        maskn copysign  = maskn_or(a_value, sign_bits);
        f32xn res       = maskn_as_f32xn(copysign);

        f32xn_store(dst + i, res);
    }
}


void f32_mul_by_sign_kernel(      f32* bad_restrict dst,
                            const f32* bad_restrict a,
                            const f32* bad_restrict reference_sign,
                                  u32               max_size)
{
    bad_assert(dst            != NULL);
    bad_assert(a              != NULL);
    bad_assert(reference_sign != NULL);
    bad_assert(max_size       != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(reference_sign);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va              = f32xn_load(a              + i);
        f32xn vreference_sign = f32xn_load(reference_sign + i);
        f32xn res             = f32xn_mul_by_sign(va, vreference_sign);

        f32xn_store(dst + i, res);
    }
}


// ========== Trigonometry ===========
void f32_cos_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_cos(vsrc);

        f32xn_store(dst + i, res);
    }
}

       
void f32_cos_0_halfpi_kernel(      f32* bad_restrict dst,
                             const f32* bad_restrict src,
                                   u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_cos_0_halfpi(vsrc);

        f32xn_store(dst + i, res);
    }
}


void f32_sin_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_sin(vsrc);

        f32xn_store(dst + i, res);
    }
}
       
void f32_sin_npi_pi_kernel(      f32* bad_restrict dst,
                           const f32* bad_restrict src,
                                 u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_sin_npi_pi(vsrc);

        f32xn_store(dst + i, res);
    }
}
       
void f32_tan_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_tan(vsrc);

        f32xn_store(dst + i, res);
    }
}
       
void f32_acos_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn vsrc = f32xn_load(src + i);
        f32xn res  = f32xn_acos(vsrc);

        f32xn_store(dst + i, res);
    }
}


// ======== Fused operations ========
void f32_mul_add_kernel(      f32* bad_restrict dst,
                        const f32* bad_restrict a,
                        const f32* bad_restrict b,
                        const f32* bad_restrict c,
                              u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(c        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);
    bad_assert_f32xn_aligned(c);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        f32xn vc  = f32xn_load(c + i);
        f32xn res = f32xn_mul_add(va, vb, vc);

        f32xn_store(dst + i, res);
    }
}


void f32_mul_sub_kernel(      f32* bad_restrict dst,
                        const f32* bad_restrict a,
                        const f32* bad_restrict b,
                        const f32* bad_restrict c,
                              u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(c        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);
    bad_assert_f32xn_aligned(c);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        f32xn vc  = f32xn_load(c + i);
        f32xn res = f32xn_mul_sub(va, vb, vc);

        f32xn_store(dst + i, res);
    }
}


void f32_nmul_add_kernel(      f32* bad_restrict dst,
                         const f32* bad_restrict a,
                         const f32* bad_restrict b,
                         const f32* bad_restrict c,
                               u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(c        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);
    bad_assert_f32xn_aligned(c);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        f32xn vc  = f32xn_load(c + i);
        f32xn res = f32xn_nmul_add(va, vb, vc);

        f32xn_store(dst + i, res);
    }
}


void f32_nmul_sub_kernel(      f32* bad_restrict dst,
                         const f32* bad_restrict a,
                         const f32* bad_restrict b,
                         const f32* bad_restrict c,
                               u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(c        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);
    bad_assert_f32xn_aligned(c);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        f32xn vc  = f32xn_load(c + i);
        f32xn res = f32xn_nmul_sub(va, vb, vc);

        f32xn_store(dst + i, res);
    }
}



// ============ Comparison ============
void f32_neq_kernel(      u32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        maskn res = f32xn_neq(va, vb);

        maskn_store(dst + i, res);
    }
}


void f32_eq_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        maskn res = f32xn_eq(va, vb);

        maskn_store(dst + i, res);
    }
}


void f32_ge_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        maskn res = f32xn_ge(va, vb);

        maskn_store(dst + i, res);
    }
}


void f32_gt_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        maskn res = f32xn_gt(va, vb);

        maskn_store(dst + i, res);
    }
}


void f32_le_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        maskn res = f32xn_le(va, vb);

        maskn_store(dst + i, res);
    }
}


void f32_lt_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(a        != NULL);
    bad_assert(b        != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(a);
    bad_assert_f32xn_aligned(b);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(a + i);
        f32xn vb  = f32xn_load(b + i);
        maskn res = f32xn_lt(va, vb);

        maskn_store(dst + i, res);
    }
}


// ======= Tests ========
void f32_is_positive_kernel(      u32* bad_restrict dst,
                            const f32* bad_restrict src,
                                  u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn zero_mask = maskn_zero();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va      = f32xn_load(src + i);

#if defined(__SSE2__) || defined(__AVX2__)
        maskn va_bits   = f32xn_as_maskn(va);
        maskn sign_only = maskn_shift_right32(va_bits, 31);
        maskn res       = maskn_eq(sign_only, zero_mask);
#else
        f32xn vzero = maskn_as_f32xn(zero_mask);
        maskn res   = f32xn_ge(va, vzero);
#endif

        maskn_store(dst + i, res);
    }
}

       
void f32_is_negative_kernel(      u32* bad_restrict dst,
                            const f32* bad_restrict src,
                                  u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn zero_mask = maskn_zero();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va      = f32xn_load(src + i);

        maskn va_bits = f32xn_as_maskn(va);
        maskn res     = maskn_gt(va_bits, zero_mask);

        maskn_store(dst + i, res);
    }
}

       
void f32_is_nan_kernel(      u32* bad_restrict dst,
                       const f32* bad_restrict src,
                             u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va  = f32xn_load(src + i);
        maskn res = f32xn_is_nan(va);

        maskn_store(dst + i, res);
    }
}

       
void f32_is_infinite_kernel(      u32* bad_restrict dst,
                            const f32* bad_restrict src,
                                  u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn value32_mask = maskn_value32();
    const maskn inf_mask     = maskn_exponent32();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va          = f32xn_load(src + i);
        maskn va_bits     = f32xn_as_maskn(va);
        maskn va_abs_bits = maskn_and(va_bits, value32_mask);
        maskn res         = maskn_eq(va_abs_bits, inf_mask);

        maskn_store(dst + i, res);
    }
}

       
void f32_is_finite_kernel(      u32* bad_restrict dst,
                          const f32* bad_restrict src,
                                u32               max_size)
{
    bad_assert(dst      != NULL);
    bad_assert(src      != NULL);
    bad_assert(max_size != 0u);
    bad_assert_f32xn_aligned(dst);
    bad_assert_f32xn_aligned(src);

    const maskn exp32_mask = maskn_exponent32();

    for (u32 i = 0u; i < max_size; i += f32xn_width)
    {
        f32xn va          = f32xn_load(src + i);
        maskn va_bits     = f32xn_as_maskn(va);
        maskn va_abs_bits = maskn_and(va_bits, exp32_mask);
        maskn res         = maskn_neq(va_abs_bits, exp32_mask);

        maskn_store(dst + i, res);
    }
}

BAD_NAMESPACE_END