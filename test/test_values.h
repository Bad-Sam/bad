#ifndef BAD_F32_VALUES_H
#define BAD_F32_VALUES_H

#include <bad/bad.h>
#include <bad/types.h>

BAD_NAMESPACE_START

static const u32 all1_bits   = 0xFFFFFFFF;
static const u32 denorm_bits = 0x8019010E;
static const u32 snan_bits   = 0x7F80E030;
static const u32 qnan_bits   = 0xFF8A6A0C;
static const u32 inf_bits    = 0x7F800000;
static const u32 ninf_bits   = 0xFF800000;
static const u32 nosign_bits = 0x7FFFFFFF;
static const u32 zero_bits   = 0x00000000;
static const u32 lower_bits  = 0x00000001;
static const u32 higher_bits = 0x80000000;

static const f32 all1   = *(f32*)&all1_bits;
static const f32 denorm = *(f32*)&denorm_bits;
static const f32 snan   = *(f32*)&snan_bits;
static const f32 qnan   = *(f32*)&qnan_bits;
static const f32 inf    = *(f32*)&inf_bits;
static const f32 lower  = *(f32*)&lower_bits;
static const f32 higher = *(f32*)&higher_bits;

BAD_NAMESPACE_END

#endif