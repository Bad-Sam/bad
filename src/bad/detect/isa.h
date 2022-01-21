#ifndef BAD_ISA_H
#define BAD_ISA_H

// Identify instruction set: x64, x86, ARM or PowerPC
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
#   define BAD_x64
#elif defined(_M_IX86) || defined(_X86_) || defined(__i386__) || defined(__i386) || defined(i386)
#   define BAD_x86
#elif defined(_M_ARM) || defined(_M_ARMT) ||  defined(__arm__)
#   define BAD_ARM32
#elif defined(_M_ARM64) || defined(__aarch64__)
#   define BAD_ARM64
#else
#   warning Unsupported instruction set architecture. The library may not work properly
#endif

#endif