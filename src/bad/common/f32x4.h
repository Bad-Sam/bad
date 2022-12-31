#ifndef BAD_F32X4_H
#define BAD_F32X4_H

#include <bad/bad.h>
#include <bad/qualifiers.h>

#include <bad/types/simd_types.h>

#include "mask128.h"

BAD_NAMESPACE_START

// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any();
static bad_forceinline f32x4 f32x4_zero();
static bad_forceinline f32x4 f32x4_half();
static bad_forceinline f32x4 f32x4_one();
static bad_forceinline f32x4 f32x4_two();


// ========== Loads & stores ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr);
static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr);
static bad_forceinline f32x4 f32x4_set(f32 a, f32 b, f32 c, f32 d);
static bad_forceinline f32x4 f32x4_set_all(f32 a);
static bad_forceinline f32x4 f32x4_set_lower(f32 a);
static bad_forceinline void bad_veccall f32x4_store(f32* mem_addr, f32x4 a);
static bad_forceinline void bad_veccall f32x4_storeu(f32* mem_addr, f32x4 a);
static bad_forceinline void bad_veccall f32x4_store_lower(f32* mem_addr, f32x4 a);


// ============== Getters =============
static bad_forceinline f32 bad_veccall f32x4_get_0(f32x4 a);
static bad_forceinline f32 bad_veccall f32x4_get_1(f32x4 a);
static bad_forceinline f32 bad_veccall f32x4_get_2(f32x4 a);
static bad_forceinline f32 bad_veccall f32x4_get_3(f32x4 a);
static bad_forceinline f32 bad_veccall f32x4_get_i(f32x4 a, u32 i);


// ============== Setters =============
static bad_forceinline f32x4 bad_veccall f32x4_copy_0(f32x4 a, f32x4 origin);
static bad_forceinline f32x4 bad_veccall f32x4_copy_1(f32x4 a, f32x4 origin);
static bad_forceinline f32x4 bad_veccall f32x4_copy_2(f32x4 a, f32x4 origin);
static bad_forceinline f32x4 bad_veccall f32x4_copy_3(f32x4 a, f32x4 origin);
static bad_forceinline f32x4 bad_veccall f32x4_set_0(f32x4 a, f32 value);
static bad_forceinline f32x4 bad_veccall f32x4_set_1(f32x4 a, f32 value);
static bad_forceinline f32x4 bad_veccall f32x4_set_2(f32x4 a, f32 value);
static bad_forceinline f32x4 bad_veccall f32x4_set_3(f32x4 a, f32 value);


// ==== Vector element broadcast =====
static bad_forceinline f32x4 bad_veccall f32x4_dup_0(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_dup_1(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_dup_2(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_dup_3(f32x4 a);


// ============ Selection =============
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4 a, f32x4 b, mask128 m);


// ======= Cast and conversion ========
static bad_forceinline mask128 bad_veccall f32x4_as_mask128(f32x4 a);
static bad_forceinline mask128 bad_veccall f32x4_to_s32x4(f32x4 a);
static bad_forceinline mask128 bad_veccall f32x4_to_u32x4(f32x4 a);


#include "f32x4/f32x4_x86-64.inl"

BAD_NAMESPACE_END

#endif