#ifndef BAD_BAD_H
#define BAD_BAD_H

#if defined(__cplusplus)
#   define BAD_NAMESPACE_START namespace bad {
#   define BAD_NAMESPACE_END }
#else
#   define BAD_NAMESPACE_START
#   define BAD_NAMESPACE_END
#endif

#if defined(__SSE__) || defined(__ARM_NEON_FP)
#   define BAD_SIMD_AVAILABLE
#endif

#endif