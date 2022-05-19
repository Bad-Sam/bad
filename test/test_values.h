#ifndef BAD_F32_VALUES_H
#define BAD_F32_VALUES_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/scalar_types.h>
#include <bad/common/u32.h>

BAD_NAMESPACE_START

static const u32 all1_bits      = 0xFFFFFFFF;
static const u32 denorm_bits    = 0x8019010E;
static const u32 snan_bits      = 0x7FA00000;
static const u32 qnan_bits      = 0x7FC00000;
static const u32 inf_bits       = 0x7F800000;
static const u32 ninf_bits      = 0xFF800000;
static const u32 nosign_bits    = 0x7FFFFFFF;
static const u32 zero_bits      = 0x00000000;
static const u32 lowbit32_bits  = 0x00000001;
static const u32 highbit32_bits = 0x80000000;

static bad_forceinline f32 all1();
static bad_forceinline f32 denorm();
static bad_forceinline f32 snan();
static bad_forceinline f32 qnan();
static bad_forceinline f32 inf();
static bad_forceinline f32 ninf();
static bad_forceinline f32 nosign();
static bad_forceinline f32 zero();
static bad_forceinline f32 lowbit32();
static bad_forceinline f32 highbit32();

#include "test_values.inl"

BAD_NAMESPACE_END

#endif