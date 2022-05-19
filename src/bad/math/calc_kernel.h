#ifndef BAD_CALC_KERNEL_H
#define BAD_CALC_KERNEL_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

// =========== Arithmetic ===========
void f32_add_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);

void f32_sub_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);
                               
void f32_mul_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);

void f32_div_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);


// ====== Advanced arithmetic =======
void f32_rcp_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size);
       
void f32_sqrt_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size);
       
void f32_rsqrt_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size);
       
void f32_min_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);

void f32_max_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);

void f32_abs_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size);
       
void f32_sign_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size);
       
void f32_neg_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size);
       
void f32_frac_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size);
       
void f32_mod_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);

void f32_trunc_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size);
       
void f32_round_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size);
       
void f32_floor_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size);
       
void f32_ceil_kernel(       f32* bad_restrict dst,
                      const f32* bad_restrict src,
                            u32               max_size);
       
void f32_clamp_kernel(      f32* bad_restrict dst,
                      const f32* bad_restrict a,
                      const f32* bad_restrict min,
                      const f32* bad_restrict max,
                            u32               max_size);

void f32_lerp_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict a,
                     const f32* bad_restrict b,
                     const f32* bad_restrict t,
                           u32               max_size);

void f32_copysign_kernel(      f32* bad_restrict dst,
                         const f32* bad_restrict a,
                         const f32* bad_restrict reference_sign,
                               u32               max_size);

void f32_mul_by_sign_kernel(      f32* bad_restrict dst,
                            const f32* bad_restrict a,
                            const f32* bad_restrict reference_sign,
                                  u32               max_size);


// ========== Trigonometry ===========
void f32_cos_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size);
       
void f32_cos_0_halfpi_kernel(      f32* bad_restrict dst,
                             const f32* bad_restrict src,
                                   u32               max_size);
       
void f32_sin_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size);
       
void f32_sin_npi_pi_kernel(      f32* bad_restrict dst,
                           const f32* bad_restrict src,
                                 u32               max_size);
       
void f32_tan_kernel(      f32* bad_restrict dst,
                    const f32* bad_restrict src,
                          u32               max_size);
       
void f32_acos_kernel(      f32* bad_restrict dst,
                     const f32* bad_restrict src,
                           u32               max_size);
       

// ======== Fused operations ========
void f32_mul_add_kernel(      f32* bad_restrict dst,
                        const f32* bad_restrict a,
                        const f32* bad_restrict b,
                        const f32* bad_restrict c,
                              u32               max_size);

void f32_mul_sub_kernel(      f32* bad_restrict dst,
                        const f32* bad_restrict a,
                        const f32* bad_restrict b,
                        const f32* bad_restrict c,
                              u32               max_size);

void f32_nmul_add_kernel(      f32* bad_restrict dst,
                         const f32* bad_restrict a,
                         const f32* bad_restrict b,
                         const f32* bad_restrict c,
                               u32               max_size);

void f32_nmul_sub_kernel(      f32* bad_restrict dst,
                         const f32* bad_restrict a,
                         const f32* bad_restrict b,
                         const f32* bad_restrict c,
                               u32               max_size);


// ============ Comparison ============
void f32_neq_kernel(      u32* bad_restrict dst,
                    const f32* bad_restrict a,
                    const f32* bad_restrict b,
                          u32               max_size);

void f32_eq_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size);

void f32_ge_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size);

void f32_gt_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size);

void f32_le_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size);

void f32_lt_kernel(      u32* bad_restrict dst,
                   const f32* bad_restrict a,
                   const f32* bad_restrict b,
                         u32               max_size);


// ======= Tests ========
void f32_is_positive_kernel(      u32* bad_restrict dst,
                            const f32* bad_restrict src,
                                  u32               max_size);
       
void f32_is_negative_kernel(      u32* bad_restrict dst,
                            const f32* bad_restrict src,
                                  u32               max_size);
       
void f32_is_nan_kernel(      u32* bad_restrict dst,
                       const f32* bad_restrict src,
                             u32               max_size);
       
void f32_is_infinite_kernel(      u32* bad_restrict dst,
                            const f32* bad_restrict src,
                                  u32               max_size);
       
void f32_is_finite_kernel(      u32* bad_restrict dst,
                          const f32* bad_restrict src,
                                u32               max_size);
       
BAD_NAMESPACE_END

#endif