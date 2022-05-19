#include <bad/bad.h>
#include <bad/debug_checks.h>
#include <bad/qualifiers.h>

#include <bad/common/f32.h>
#include <bad/common/u32.h>
#include <bad/common/f32x4.h>
#include <bad/common/f32x8.h>
#include <bad/common/f32xn.h>
#include <bad/common/mask128.h>
#include <bad/common/mask256.h>
#include <bad/common/maskn.h>

#include <bad/detect/builtin.h>
#include <bad/detect/isa.h>
#include <bad/detect/os.h>
#include <bad/detect/os.h>

#include <bad/math/constants.h>
#include <bad/math/f32_calc.h>
#include <bad/math/f32x4_calc.h>
#include <bad/math/f32x8_calc.h>
#include <bad/math/f32xn_calc.h>
#include <bad/math/vec3.h>
#include <bad/math/vec4.h>
#include <bad/math/quat.h>
#include <bad/math/calc_kernel.h>
#include <bad/math/vec4_kernel.h>

#include <bad/types/math_types.h>
#include <bad/types/scalar_types.h>
#include <bad/types/simd_types.h>

#include <stdio.h>

BAD_USE_NAMESPACE

int main()
{

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

// Register approximation functions
func_f32 functions[] =
{
    ADD_FUNC_F32(acosf),
    ADD_FUNC_F32(f32_acos),
};

func_f32 ref_func = ADD_FUNC_F32(acosf);

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
                "- max_rel_err = %.12f %%\n"
                "- max_err_x   = %.12f\n",
                functions[i].name,
                functions[i].max_err,
                functions[i].max_rel_err,
                functions[i].max_err_x);
    }
}


int main()
{
    mesure_accuracy(-1.f, 1.f, .000001f);
}*/