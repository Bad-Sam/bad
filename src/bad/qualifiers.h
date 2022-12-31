#ifndef BAD_QUALIFIERS_H
#define BAD_QUALIFIERS_H

// bad_veccall
#if defined(__SSE__)
#   if defined(_MSC_VER) && _MSC_VER >= 1800 && !defined(_MANAGED) && !defined(_M_CEE) && (defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP > 1))
#      define bad_veccall _vectorcall
#   elif defined(__clang__) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ > 5))
#      define bad_veccall __vectorcall
#   endif
#   if defined(bad_veccall)
#       define BAD_VECTORCALL_AVAILABLE
#   else
#      define bad_veccall
#   endif
#else
#   define bad_veccall
#endif

// bad_align
#if defined(__GNUC__) || defined(__clang__)
#   define bad_align_to(x) __attribute__((aligned(sizeof(x))))
#elif defined(_MSC_VER)
#   define bad_align_to(x) __declspec(align(sizeof(x)))
#else
#   define bad_align_to(x) _Alignas(sizeof(x))
#endif

// bad_restrict
#if defined(__cplusplus)
#   define bad_restrict __restrict
#elif defined(__clang__) || defined(__GNUC__)
#   define bad_restrict restrict
#else
#   define bad_restrict
#endif

// bad_inline
#if defined(_MSC_VER)
#   define bad_inline __inline
#else
#   define bad_inline inline
#endif

// bad_forceinline
#if defined(_MSC_VER)
#   define bad_forceinline __forceinline
#elif __has_attribute(always_inline)
#   define bad_forceinline __attribute__((always_inline)) bad_inline
#else
#   define bad_forceinline bad_inline
#endif

#endif
