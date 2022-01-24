# Resources
This is a glossary of all the resources I used to develop the code in this repository.  
Resources I found especially helpful are in **bold**.

## Libraries
- Nicholas Frechette's [Real Time Math (RTM)](https://github.com/nfrechette/rtm)
- DLTcollab's [sse2neon](https://github.com/DLTcollab/sse2neon) (Intel SSE intrinsics to ARM/ARM64 Neon instrinsics


## Compilers ##
### MSVC
- ["Introducing ‘Vector Calling Convention’" article](https//devblogs.microsoft.com/cppblog/introducing-vector-calling-convention/)
- [MSVC predefined macros](https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-160)
- [`__vectorcall` usage macro requirements](https://github.com/microsoft/STL/blob/9a9820df1a1d3fa84100e3169ff37fdd4fa41759/stl/inc/xstddef#L322)
- [`inline` functions](https://docs.microsoft.com/en-us/cpp/cpp/inline-functions-cpp)

### Clang
- [`__vectorcall` start of support release note](https://releases.llvm.org/3.6.0/tools/clang/docs/ReleaseNotes.html#windows-support)
- [`align_value` attribute](https://clang.llvm.org/docs/AttributeReference.html#align-value)


## Tools ##
- [IEEE-754 floating point converter](https://www.h-schmidt.net/FloatConverter/IEEE754.html)


## C/C++ language features ##
- [C++ reference](https://en.cppreference.com/w/)
- [IEEE-754 floating point numbers](https://steve.hollasch.net/cgindex/coding/ieeefloat.html)


## Optimization ##
### General
- **[Agner Fog's software optimization resources](https://www.agner.org/optimize/)**
- **[Stack Overflow](https://stackoverflow.com/)**
- [Fastest way to compute absolute value using SSE](https://stackoverflow.com/questions/32408665/fastest-way-to-compute-absolute-value-using-sse)
- [Fastest way to do horizontal SSE vector sum or other reduction](https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-sse-vector-sum-or-other-reduction/35270026#35270026)
- **[Table of latency, throughput and port usage by micro-operation](https://www.uops.info/table.html)**
- **[The uops.info code analyzer](https://uica.uops.info/)**
- [SIMD at Insomniac Games](https://deplinenoise.files.wordpress.com/2015/03/gdc2015_afredriksson_simd.pdf)

### Memory access
- [Memory part 5: what programmers can do](https://lwn.net/Articles/255364/)

### Math
- [Chebyshev-approximation-based sin(x) implementation](https://web.archive.org/web/20200628195036/http://mooooo.ooo/chebyshev-sine-approximation/)
- [Fast math function implementation](https://stackoverflow.com/questions/18662261/fastest-implementation-of-sine-cosine-and-square-root-in-c-doesnt-need-to-b)

### SIMD ISAs (SSE & AVX)

**Intel**
- [Intel intrinsics C headers](https://stackoverflow.com/questions/11228855/header-files-for-x86-simd-intrinsics)
- **[All Intel intrinsics](https://web.archive.org/web/20211009193322/https://software.intel.com/sites/landingpage/IntrinsicsGuide/)**
- [All Intel intrinsics (offline version)](https://software.intel.com/content/dam/develop/public/us/en/downloads/intel-intrinsics-guide-offline-v3.6.0.zip)
- [SIMD and AVX512](https://www.uio.no/studier/emner/matnat/ifi/IN3200/v19/teaching-material/avx512.pdf)
- [AVX512 performance issues](https://extensa.tech/blog/avx-throttling-part1/)
- [Kosta's "SIMD for C++ developers"](http://const.me/articles/simd/simd.pdf)


**ARM**
- [ABI for all ARM architectures](https://github.com/ARM-software/abi-aa)
- [Overview of the ARM32 ABI convention](https://docs.microsoft.com/en-us/cpp/build/overview-of-arm-abi-conventions?view=msvc-160)
- [Overview of the ARM64 ABI convention](https://docs.microsoft.com/en-us/cpp/build/arm64-windows-abi-conventions?view=msvc-160)

#### Neon
- [ARM SIMD ISAs](https://developer.arm.com/architectures/instruction-sets/simd-isas)
- **[All Neon intrinsics](https://developer.arm.com/architectures/instruction-sets/intrinsics/)**
- [Optimizing C Code with NEON Intrinsics](https://developer.arm.com/documentation/102467/0100/)
- [Maximum vector parameters passed in registers](https://docs.microsoft.com/en-us/cpp/build/overview-of-arm-abi-conventions?view=msvc-160#parameter-passing)

#### Helium
- [ARM Helium technology](https://developer.arm.com/architectures/instruction-sets/simd-isas/helium)
- [Introduction to ARM's Helium](https://developer.arm.com/documentation/102102/0102)
- [Helium Programmer's Guide: Coding for Helium](https://developer.arm.com/documentation/102095/0100/)


**PowerPC**
#### AltiVec
- [GCC's AltiVec/VSX built-in functions record](https://gcc.gnu.org/onlinedocs/gcc/PowerPC-AltiVec_002fVSX-Built-in-Functions.html)
- [OpenPOWER foundation resource catalog](https://openpowerfoundation.org/technical/resource-catalog/)
- [64-bit PowerPC ABI (April 2021)](https://cdn.openpowerfoundation.org/wp-content/uploads/2021/04/leabi-20201201.pdf)
- [Power vector intrinsics programming reference](https://cdn.openpowerfoundation.org/wp-content/uploads/resources/Intrinsics-Reference_final/Intrinsics-Reference-20200811.pdf)


**General**  
- [Compiler intrinsics explanation across compilers and CPU architectures, compilation options, C macros, and more](https://www.linuxjournal.com/content/introduction-gcc-compiler-intrinsics-vector-processing)

## Power consumption
- [Power Consumption of Performance-Scaled SIMD Processors](https://link.springer.com/chapter/10.1007/978-3-540-30205-6_55)
- [How SIMD width affects energy efficiency: a case study on sorting](https://researcher.watson.ibm.com/researcher/files/jp-INOUEHRS/COOLChips_SIMDsort_slides.pdf)
- [Do SSE instructions consume more power/energy?](https://stackoverflow.com/questions/19722950/do-sse-instructions-consume-more-power-energy)
- [Parallelism and the ARM Instruction Set Architecture](https://www.ics.uci.edu/~eli/courses/cs244-w12/arm.pdf)
- [Code transformations and SIMD impact on embedded software energy/power consumption](https://www.academia.edu/50780003/Code_transformations_and_SIMD_impact_on_embedded_software_energy_power_consumption)

