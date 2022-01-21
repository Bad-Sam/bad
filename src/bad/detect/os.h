#ifndef BAD_OS_H
#define BAD_OS_H

// OS detection
#if defined(__linux__)
#   define BAD_LINUX
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__NT__) || defined(__CYGWIN__)
#   define BAD_WINDOWS
#else
#   warning Unsupported OS. The library may not work properly
#endif


// OS-specific macro definition/undefinition
#if defined(BAD_WINDOWS)
#   define _CRT_SECURE_NO_WARNINGS
#   define NOMINMAX
#endif

#endif
