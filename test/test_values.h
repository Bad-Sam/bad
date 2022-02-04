#ifndef BAD_F32_VALUES_H
#define BAD_F32_VALUES_H

#include <bad/bad.h>
#include <bad/types.h>

BAD_NAMESPACE_START

#if !defined(__SSE2__) && defined(__SSE__)
#   define BAD_TEST_F32_MASK
    static const u32 all1_bits      = 0xFFFFFFFF;
    static const u32 denorm_bits    = 0x8019010E;
    static const u32 snan_bits      = 0x7F80E030;
    static const u32 qnan_bits      = 0xFF8A6A0C;
    static const u32 inf_bits       = 0x7F800000;
    static const u32 ninf_bits      = 0xFF800000;
    static const u32 nosign_bits    = 0x7FFFFFFF;
    static const u32 zero_bits      = 0x00000000;
    static const u32 lowbit32_bits  = 0x00000001;
    static const u32 highbit32_bits = 0x80000000;

    static const f32 all1      = *(f32*)&all1_bits;
    static const f32 denorm    = *(f32*)&denorm_bits;
    static const f32 snan      = *(f32*)&snan_bits;
    static const f32 qnan      = *(f32*)&qnan_bits;
    static const f32 inf       = *(f32*)&inf_bits;
    static const f32 ninf      = *(f32*)&ninf_bits;
    static const f32 zero      = *(f32*)&zero_bits;
    static const f32 lowbit32  = *(f32*)&lowbit32_bits;
    static const f32 highbit32 = *(f32*)&highbit32_bits;
    
#   define all1f      all1;
#   define denormf    denorm;
#   define snanf      snan;
#   define qnanf      qnan;
#   define inff       inf;
#   define ninff      ninf;
#   define zerof      zero;
#   define lowbit32f  lowbit32;
#   define highbit32f highbit32;
#else
    static const u32 all1       = 0xFFFFFFFF;
    static const u32 denorm     = 0x8019010E;
    static const u32 snan       = 0x7F80E030;
    static const u32 qnan       = 0xFF8A6A0C;
    static const u32 inf        = 0x7F800000;
    static const u32 ninf       = 0xFF800000;
    static const u32 nosign     = 0x7FFFFFFF;
    static const u32 zero       = 0x00000000;
    static const u32 lowbit32   = 0x00000001;
    static const u32 highbit32  = 0x80000000;

    static const f32 all1f      = *(f32*)&all1;
    static const f32 denormf    = *(f32*)&denorm;
    static const f32 snanf      = *(f32*)&snan;
    static const f32 qnanf      = *(f32*)&qnan;
    static const f32 inff       = *(f32*)&inf;
    static const f32 zerof      = *(f32*)&zero;
    static const f32 lowbit32f  = *(f32*)&lowbit32;
    static const f32 highbit32f = *(f32*)&highbit32;
#endif

BAD_NAMESPACE_END

#endif