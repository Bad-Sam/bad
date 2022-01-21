#ifndef BAD_F32_VALUES_H
#define BAD_F32_VALUES_H

#include <bad/bad.h>
#include <bad/types.h>

BAD_NAMESPACE_START

static const u32 denorm_bits = 0x0019010E;
static const u32 snan_bits   = 0x7F80E030;
static const u32 qnan_bits   = 0xFF8A6A0C;

static const f32 inf    = 1.f / .0f;
static const f32 denorm = *(f32*)&denorm_bits;
static const f32 snan   = *(f32*)&snan_bits;
static const f32 qnan   = *(f32*)&qnan_bits;

#if !defined(__SSE2__) && defined(__SSE__)
    static const u32 all1_bits = 0xFFFFFFFF;
    static const f32 all1      = *(f32*)&all1_bits;
#endif

BAD_NAMESPACE_END

#endif