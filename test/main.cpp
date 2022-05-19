#include "tests/test_mask128.h"
#include "tests/test_mask256.h"
#include "tests/test_f32x4.h"
#include "tests/test_f32x8.h"
#include "tests/test_f32x4_calc.h"
#include "tests/test_f32x8_calc.h"
#include "tests/test_vec3.h"
#include "tests/test_vec4.h"
#include "tests/test_vec4_kernel.h"

#if defined(__cplusplus)
using namespace bad;
#endif

int main()
{
    fprintf(stderr, "========== mask128.h ==========");
    test_mask128_load_store();
    test_mask128_loadu_storeu();
    test_mask128_set();
    test_mask128_set_all();
    test_mask128_zero();
    test_mask128_all1();
    test_mask128_value32();
    test_mask128_highbit32();
    test_mask128_lowbit32();
    test_mask128_exponent32();
    test_mask128_eq();
    test_mask128_neq();
    test_mask128_and();
    test_mask128_and_not();
    test_mask128_or();
    test_mask128_xor();
    test_mask128_not();

    fprintf(stderr, "\n\n========== mask256.h ==========");
    test_mask256_load_store();
    test_mask256_loadu_storeu();
    test_mask256_set();
    test_mask256_set_all();
    test_mask256_zero();
    test_mask256_all1();
    test_mask256_value32();
    test_mask256_highbit32();
    test_mask256_lowbit32();
    test_mask256_exponent32();
    test_mask256_eq();
    test_mask256_neq();
    test_mask256_and();
    test_mask256_and_not();
    test_mask256_or();
    test_mask256_xor();
    test_mask256_not();

    fprintf(stderr, "\n\n========== f32x4.h ==========");
    test_f32x4_zero();
    test_f32x4_one();
    test_f32x4_load_store();
    test_f32x4_loadu_storeu();
    test_f32x4_set();
    test_f32x4_set_all();
    test_f32x4_blend();
    test_f32x4_as_mask128();

    fprintf(stderr, "\n\n========== f32x8.h ==========");
    test_f32x8_zero();
    test_f32x8_one();
    test_f32x8_load_store();
    test_f32x8_loadu_storeu();
    test_f32x8_set();
    test_f32x8_set_all();
    test_f32x8_blend();
    test_f32x8_as_mask256();

    fprintf(stderr, "\n\n========== f32x8_calc.h ==========");
    test_f32x8_hadd();
    test_f32x8_hadd();
    test_f32x8_abs();
    test_f32x8_sign();
    test_f32x8_neg();
    test_f32x8_frac();
    test_f32x8_mod();
    test_f32x8_trunc();
    test_f32x8_round();
    test_f32x8_floor();
    test_f32x8_ceil();
    test_f32x8_clamp();
    test_f32x8_lerp();
    test_f32x8_mul_add();
    test_f32x8_mul_sub();
    test_f32x8_nmul_add();
    test_f32x8_nmul_sub();
    test_f32x8_neq();
    test_f32x8_eq();
    test_f32x8_ge();
    test_f32x8_gt();
    test_f32x8_le();
    test_f32x8_lt();
    test_f32x8_is_nan();
    test_f32x8_is_infinite();
    test_f32x8_is_finite();

    fprintf(stderr, "\n\n========== f32x4_calc.h ==========");
    test_f32x4_hadd3();
    test_f32x4_hadd4();
    test_f32x4_sum3();
    test_f32x4_sum4();
    test_f32x4_abs();
    test_f32x4_sign();
    test_f32x4_neg();
    test_f32x4_frac();
    test_f32x4_mod();
    test_f32x4_trunc();
    test_f32x4_round();
    test_f32x4_floor();
    test_f32x4_ceil();
    test_f32x4_clamp();
    test_f32x4_lerp();
    test_f32x4_mul_add();
    test_f32x4_mul_sub();
    test_f32x4_nmul_add();
    test_f32x4_nmul_sub();
    test_f32x4_sin();
    test_f32x4_neq();
    test_f32x4_eq();
    test_f32x4_ge();
    test_f32x4_gt();
    test_f32x4_le();
    test_f32x4_lt();
    test_f32x4_is_nan();
    test_f32x4_is_infinite();
    test_f32x4_is_finite();

    fprintf(stderr, "\n\n========== vec3.h ==========");
    test_vec3_cross();
    
    fprintf(stderr, "\n\n========== vec4.h ==========");
    test_vec4_dot();
    test_vec4_length_squared();
    test_vec4_length();
    test_vec4_lerp();

    fprintf(stderr, "\n\n========== vec4_kernel.h ==========");
    test_vec4_ker_dot();
    test_vec4_ker_length_squared();
    test_vec4_ker_length();

    test_report();

    return 0;
}

/*
int main()
{
    const u32 vec_count = 1000000;
    const u32 f32_count = vec_count * 8u;
    f32*  elem          = (f32*)_mm_malloc(f32_count * sizeof(f32), 32u);
    f32*  res           = (f32*)_mm_malloc(f32_count * sizeof(f32), 32u);

    s64 cycles = 0;
    s64 t0 = get_perf_counter();

#if 0
    for (u32 i = 0u; i < f32_count; i++)
    {
        res[i] = f32_acos(elem[i]);
    }
#else
    f32_acos_kernel(res, elem, f32_count);
#endif

    s64 t1 = get_perf_counter();
    cycles += t1 - t0;



    asm volatile("" : : "r,m"(res) : "memory");
    fprintf(stderr, "\n%lli cycles (%.3f cycles per element)", cycles, (f32)cycles / f32_count);

    _mm_free(res);
    _mm_free(elem);

    return 0;
}
*/