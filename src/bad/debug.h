#ifndef BAD_DEBUG_H
#define BAD_DEBUG_H

#if defined(DEBUG) || defined(_DEBUG)
#   include <bad/detect/isa.h>
#endif

# define bad_func __func__

// bad_interrupt
#if defined(_MSC_VER)
#   if defined(BAD_x64)
        // NOTE: Assembly block seem to be forbidden with x64 MSVC?
#       include <intrin.h>
#       define bad_interrupt(x) __debugbreak()
#   elif defined(BAD_x86)
#       define bad_interrupt(x) __asm { int (x) }
#   endif
#elif defined(__clang__) || defined(__GNUC__)
#   define bad_interrupt(x) __asm__("int"#x)
#else
#   define bad_interrupt(x) exit((x))
#endif

// bad_assert
#if defined(DEBUG) || defined(_DEBUG)
#   include <stdio.h>

    // bad_assert
#   define bad_assert(x)                                               \
    do                                                                 \
    {                                                                  \
        if ((x))                                                       \
        {}                                                             \
        else                                                           \
        {                                                              \
            fprintf(stderr, "\nAssertion failed in %s: %s\n(%s:%i)\n", \
                    bad_func, #x, __FILE__, __LINE__);                 \
            bad_interrupt(3);                                          \
        }                                                              \
    }                                                                  \
    while (0)

    // bad_assert_aligned
#   define bad_assert_aligned(ptr, alignment)                                                        \
    do                                                                                               \
    {                                                                                                \
        if ((size_t)(ptr) % (size_t)(alignment) == 0)                                                \
        {}                                                                                           \
        else                                                                                         \
        {                                                                                            \
            fprintf(stderr, "\nVariable %s in %s is not %i-bytes aligned, but should be\n(%s:%i)\n", \
                    #ptr, bad_func, alignment, __FILE__, __LINE__);                                  \
            bad_interrupt(3);                                                                        \
        }                                                                                            \
    }                                                                                                \
    while (0)

#define bad_assert_sse_aligned(ptr)   bad_assert_aligned((ptr), 16)
#define bad_assert_avx_aligned(ptr)   bad_assert_aligned((ptr), 32)
#define bad_assert_f32xn_aligned(ptr) bad_assert_aligned((ptr), (f32xn_width * 4))
#else
#   define bad_assert(x)                      do {} while (0)
#   define bad_assert_aligned(ptr, alignment) do {} while (0)
#   define bad_assert_sse_aligned(ptr)        do {} while (0)
#   define bad_assert_avx_aligned(ptr)        do {} while (0)
#   define bad_assert_f32xn_aligned(ptr)      do {} while (0)
#endif

#endif