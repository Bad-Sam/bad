#ifndef BAD_BUILTIN_H
#define BAD_BUILTIN_H

#if defined(__has_builtin)
#   define bad_has_builtin(builtin) __has_builtin(builtin)
#else
#   define bad_has_builtin(builtin) 0
#endif

#endif