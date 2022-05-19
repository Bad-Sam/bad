#ifndef BAD_DEBUG_CHECKS_H
#define BAD_DEBUG_CHECKS_H

#if defined(DEBUG) || defined(_DEBUG)
#   include <bad/detect/isa.h>
#endif

// bad_interrupt
#if defined(__clang__) || defined(__GNUC__)
#   define bad_interrupt() do { __asm__("int3"); } while (0)
#elif defined(_MSC_VER)
#   if defined(BAD_x64)
#       include <intrin.h>
#       define bad_interrupt() do { __debugbreak(); } while (0)
#   elif defined(BAD_x86)
#       define bad_interrupt() do { __asm { int3 }; } while (0)
#   endif
#else
#   include <stdlib.h>
#   define bad_interrupt() do { exit(EXIT_FAILURE); } while (0)
#endif


// bad_assert
#if defined(DEBUG) || defined(_DEBUG)
#   include <stdio.h>

#   define bad_assert(x)                                               \
    do                                                                 \
    {                                                                  \
        if ((x))                                                       \
        {}                                                             \
        else                                                           \
        {                                                              \
            fprintf(stderr, "\nAssertion failed in %s: %s\n(%s:%i)\n", \
                    __func__, #x, __FILE__, __LINE__);                 \
            bad_interrupt();                                           \
        }                                                              \
    }                                                                  \
    while (0)

#   define bad_assert_aligned(ptr, alignment)                                                        \
    do                                                                                               \
    {                                                                                                \
        if ((size_t)(ptr) % (size_t)(alignment) == 0)                                                \
        {}                                                                                           \
        else                                                                                         \
        {                                                                                            \
            fprintf(stderr, "\nVariable %s in %s is not %i-bytes aligned, but should be\n(%s:%i)\n", \
                    #ptr, __func__, alignment, __FILE__, __LINE__);                                  \
            bad_interrupt();                                                                         \
        }                                                                                            \
    }                                                                                                \
    while (0)

// bad_assert
#define bad_assert_sse_aligned(ptr)   bad_assert_aligned((ptr), 16u)
#define bad_assert_avx_aligned(ptr)   bad_assert_aligned((ptr), 32u)
#define bad_assert_f32xn_aligned(ptr) bad_assert_aligned((ptr), (f32xn_width * 4u))
#define bad_assert_maskn_aligned(ptr) bad_assert_aligned((ptr), (maskn_width * 4u))
#else
#   define bad_assert(x)                      do {} while (0)
#   define bad_assert_aligned(ptr, alignment) do {} while (0)
#   define bad_assert_sse_aligned(ptr)        do {} while (0)
#   define bad_assert_avx_aligned(ptr)        do {} while (0)
#   define bad_assert_f32xn_aligned(ptr)      do {} while (0)
#endif

#endif