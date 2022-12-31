#ifndef BAD_OS_H
#define BAD_OS_H

// OS detection
#if defined(__linux__)
#   define BAD_LINUX 1
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__NT__) || defined(__CYGWIN__)
#   define BAD_WINDOWS 1
#   if !defined(_CRT_SECURE_NO_WARNINGS)
#       define _CRT_SECURE_NO_WARNINGS
#   endif
#   if !defined(NOMINMAX)
#       define NOMINMAX
#       define WIN32_LEAN_AND_MEAN
#   endif
#endif

#endif
