# bad

A C/C++ SIMD math library for video game programming and connected fields, targeting x86, x86-64 and ARM architectures. `bad` aims at providing a math library, but might be extended to offer systems, modules and algorithms commonly used in the video game industry (collision, physics, etc.).


## Disclaimer
Because I am working on this library primarily to learn, it is a work in progress in its early days. It is missing a lot of features and may contain dirty and incorrect code.


## Goals of the library
- Provide a cross-platform optimized API
- Compile with Clang, GCC and MSVC
- Compile and run under Windows and Linux
- Both C and C++ compatible
- Take advantage of the available SIMD instruction sets
- Offer the best performance for mathematics (and other modules and algorithms commonly found in the video game industry) for low energy consumption
- Provide a library with no dependencies that relies as little as possible on the standard C/C++ library


## Current state of the library
- Tested on a laptop with an AMD x86-64 CPU (Ryzen 7 5800H)
- Compiled with Clang
- Compiled under Windows 10
- C++ compatible
- Takes advantage of MMX, SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, AVX, AVX2 and FMA intrinsics
- Contains only common single-precision floating-point vector operations
- Has no dependency, but relies on `stdint.h`


## Repository overview
- [`src/bad/`](src/bad/): the library. If you want to use `bad` in your project, this is probably the only directory you need
    - [`common/`](src/bad/common/): common operations likely to be used throughout the rest of the library
    - [`detect/`](src/bad/detect/): context detection around the library
    - [`math/`](src/bad/math/): math functions
    - [`args.h`](src/bad/args.h): the way arguments are passed to functions has an influence on performance. `arg.h` wraps behind macros the ideal argument passing method for all types
    - [`bad.h`](src/bad/bad.h): included accross all headers, currently used solely for wrapping sources in an optional namespace
    - [`debug.h`](src/bad/debug.h): debug-mode runtime checks through macros
    - [`qualifiers.h`](src/bad/qualifiers.h): a variety of qualifiers used to affect how the compiler generates code
    - [`types.h`](src/bad/types.h): where data types available to the library are included, declared and typedef'ed
- [`test/`](test/): unit tests on important and/or non-trivial functions
- [`build.bat`](build.bat/): custom compilation script for Windows 10 with Clang. Can be called with `build`, `build run`, `build clean` or `build asm`
- [`RESOURCES.md`](RESOURCES.md): a collection knowledge that helped me learn

## To do
General:
- [ ] Work on C/C++ interoperability
- [ ] Work on Linux support
- [ ] Support compilation with GCC and MSVC
- [ ] Support compilation under ARM
- [ ] Add support for more SIMD instruction sets (RISC-V "V", PowerPC's AltiVec, MIPS' MSA, ARM's Helium?)
- [ ] Take endianness in consideration

Common:
- [ ] Implement `f32xn` and `maskn`, a general vector type built on top of the most suited SIMD ISA available for the needs of the user
- [ ] Explore non-temporal loads and stores
- [ ] Explore possible implementation of types whose size is not a multiple of the available vector width (vec2 and vec3 for instance)
- [ ] Remove the dependency on `stdint.h` in [`types.h`](src/bad/types.h)
- [ ] Learn about interoperability and penalties between ISA (SSE <--> AVX for instance), and manage them

Tests:
- [ ] Extend tests to all functions, trivial or not
- [ ] Improve testing framework?

Math:
- [ ] Migrate calculus/mathematical functions in `common/f32x4.h` to `math`
- [ ] Implement common calculus functions such as power, exponential, log, cos, sin, tan...
- [ ] Implement 4-dimensional vector
- [ ] Implement 3-dimensional vector
- [ ] Implement quaternion
- [ ] Implement 4x4, 3x4 and 3x3 matrices
- [ ] Implement math types conversion functions
- [ ] Implement common splines

Collisions & intersections:
- [ ] Implement shapes
- [ ] Implementation collision algorithms

Physics:
- [ ] Implement kinematic


## License

`bad` is licensed under the [MIT license](LICENSE)