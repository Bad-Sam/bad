#ifndef BAD_DEBUG_CHECKS_H
#define BAD_DEBUG_CHECKS_H

// Runtime debug checks performed depending on ENABLE_DEBUG_MODE macro definition and value
// - ENABLE_DEBUG_MODE not defined: no debug checks are performed, debug macros evaluate to nothing
// - ENABLE_DEBUG_MODE set to `1`: debug checks are performed and output a message on failure
// - ENABLE_DEBUG_MODE set to `2`: debug checks are performed and output a message on failure and trigger a debug break
#if defined(ENABLE_DEBUG_MODE) && (ENABLE_DEBUG_MODE == 1 || ENABLE_DEBUG_MODE == 2)
#   include <bad/types/scalar_types.h>

// bad_debug_write_literal
// stderr file descriptor is always 2
#   if defined(_MSC_VER)
#       include <io.h>
#       define bad_debug_write_literal(msg) _write(2, msg, sizeof(msg) - 1u)
#   else
#       include <unistd.h>
#       define bad_debug_write_literal(msg) write(2, msg, sizeof(msg) - 1u)
#   endif

// bad_interrupt
#   if defined(_MSC_VER)
#      include <windows.h>
#      define bad_debug_breakpoint() do { __debugbreak(); } while (0)
#   elif defined(__has_builtin) && __has_builtin(__builtin_trap)
#       define bad_debug_breakpoint() do { __builtin_trap(); } while (0)
#   elif defined(__clang__) || defined(__GNUC__)
#       define bad_debug_breakpoint() do { __asm__("int3"); } while (0)
#   else
#      include <stdlib.h>
#      define bad_debug_breakpoint() do { abort(); } while (0)
#   endif

// bad_debug_check
#   if ENABLE_DEBUG_MODE == 1
#       define bad_debug_check_failed()
#   elif ENABLE_DEBUG_MODE == 2
#       define bad_debug_check_failed() bad_debug_breakpoint()
#   endif

#   define BAD_TO_STR_DEPTH(x) #x
#   define BAD_TO_STR(x)       BAD_TO_STR_DEPTH(x)

#   define bad_debug_check(x)                                                                            \
    do                                                                                                   \
    {                                                                                                    \
        if (!(x))                                                                                        \
        {                                                                                                \
            bad_debug_write_literal("\n" __FILE__ ":" BAD_TO_STR(__LINE__) ": " #x " returned false\n"); \
            bad_debug_check_failed();                                                                    \
        }                                                                                                \
    }                                                                                                    \
    while (0)

// bad_debug_check_aligned
#   define bad_debug_check_aligned(ptr, type) bad_debug_check(((size_t)ptr % sizeof(type)) == 0) 
#else
#   define bad_debug_write_literal(msg)       do {} while (0)
#   define bad_debug_breakpoint()             do {} while (0)
#   define bad_debug_check_failed()           do {} while (0)
#   define bad_debug_check(x)                 do {} while (0)
#   define bad_debug_check_aligned(ptr, type) (void)ptr
#endif

#endif
