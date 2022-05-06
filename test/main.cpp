#include "test.h"
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

    //__int32 a;

    return 0;
}

/*
// ========== Tests ==========
typedef struct
{
    const char* name;
    f32 (*func)(f32 a);
    f32 max_err;
    f32 max_rel_err;
    f32 max_err_x;
    s64 perf;
} func_f32;


#define ADD_FUNC_F32(a) {#a, a, .0f, .0f, .0f, 0}

// Register cos approximation functions
func_f32 functions[] =
{
    ADD_FUNC_F32(sinf),
    ADD_FUNC_F32(f32_sin),
};

func_f32 ref_func = ADD_FUNC_F32(sinf);

void mesure_accuracy(f32 start, f32 end, f32 step)
{
    // Compute constants
    const s32 functions_size = sizeof(functions) / sizeof(functions[0]);

    // Test each functions
    for (s32 i = 0; i < functions_size; i++)
    {
        func_f32* tested_func = functions + i;

        for (f32 x = start; x < end; x += step)
        {
            f32 ref_x  = (*ref_func.func)(x);
            f32 func_x = (*tested_func->func)(x);
            f32 err     = f32_abs(ref_x - func_x);

            if (tested_func->max_err < err)
            {
                tested_func->max_err     = err;
                tested_func->max_rel_err = 100.f * err / ref_x;
                tested_func->max_err_x   = x;
            }
        }
    }

    // Display results
    for (s32 i = 0; i < functions_size; i++)
    {
        fprintf(stderr,
                "\n%s:\n"
                "- max_err     = %.12f\n"
                "- max_rel_err = %.12f\n"
                "- max_err_x   = %.12f\n",
                functions[i].name,
                functions[i].max_err,
                functions[i].max_rel_err,
                functions[i].max_err_x);
    }
}


void mesure_perf(f32 start, f32 end, f32 step)
{
    // Compute constants
    const s32 functions_size = sizeof(functions) / sizeof(functions[0]);
    const s64 elem_count    = (end - start) / step;

    // Test each functions
    for (s32 i = 0; i < functions_size; i++)
    {
        func_f32* tested_func = functions + i;
        s64       perf_sum    = 0;

        for (f32 x = start; x < end; x += step)
        {
            s64 t0     = get_perf_counter();
            f32 func_x = (*tested_func->func)(x);
            s64 t1     = get_perf_counter();

            perf_sum += t1 - t0;

            asm volatile("" : : "r,m"(func_x) : "memory");
        }

        functions[i].perf = perf_sum;
    }

    // Show results
    for (s32 i = 0; i < functions_size; i++)
    {
        fprintf(stderr,
                "\n%s:\n"
                "- elem_count = %lli\n"
                "- perf   = %llif\n",
                functions[i].name,
                elem_count,
                functions[i].perf);
    }
}*/