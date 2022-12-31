#ifndef BAD_MASK128_H
#define BAD_MASK128_H

#include <bad/bad.h>
#include <bad/qualifiers.h>

#include <bad/types/simd_types.h>
#include <bad/debug_checks.h>

BAD_NAMESPACE_START

// ========== Load & store ==========
static bad_forceinline mask128 mask128_load(const mask_elem* mem_addr);
static bad_forceinline mask128 mask128_loadu(const mask_elem* mem_addr);
static bad_forceinline mask128 mask128_set(mask_elem a, mask_elem b, mask_elem c, mask_elem d);
static bad_forceinline mask128 mask128_set_all(mask_elem k);
static bad_forceinline void bad_veccall mask128_store(mask_elem* mem_addr, mask128 a);
static bad_forceinline void bad_veccall mask128_storeu(mask_elem* mem_addr, mask128 a);


// ========== Common masks ==========
static bad_forceinline mask128 mask128_zero();
static bad_forceinline mask128 mask128_all1();
static bad_forceinline mask128 mask128_value32();
static bad_forceinline mask128 mask128_highbit32();
static bad_forceinline mask128 mask128_lowbit32();
static bad_forceinline mask128 mask128_exponent32();


// ======= Masking operations =======
static bad_forceinline mask128 bad_veccall mask128_keep_highbit32(mask128 a);
static bad_forceinline mask128 bad_veccall mask128_keep_lowbit32(mask128 a);
static bad_forceinline mask128 bad_veccall mask128_shift_left32(mask128 a, s32 shift);
static bad_forceinline mask128 bad_veccall mask128_shift_right32(mask128 a, s32 shift);


// ============== Getters =============
static bad_forceinline mask_elem bad_veccall mask128_get_0(mask128 a);
static bad_forceinline mask_elem bad_veccall mask128_get_1(mask128 a);
static bad_forceinline mask_elem bad_veccall mask128_get_2(mask128 a);
static bad_forceinline mask_elem bad_veccall mask128_get_3(mask128 a);


// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128 a, mask128 b);
static bad_forceinline mask128 mask128_neq(mask128 a, mask128 b);
static bad_forceinline mask128 mask128_gt(mask128 a, mask128 b);


// ======= Bitwise operations =======
static bad_forceinline mask128 bad_veccall mask128_and(mask128 a, mask128 b);
static bad_forceinline mask128 bad_veccall mask128_and_not(mask128 a, mask128 b);
static bad_forceinline mask128 bad_veccall mask128_or(mask128 a, mask128 b);
static bad_forceinline mask128 bad_veccall mask128_xor(mask128 a, mask128 b);
static bad_forceinline mask128 bad_veccall mask128_not(mask128 a);


// ======== Cast & conversion =========
static bad_forceinline f32x4 bad_veccall mask128_as_f32x4(mask128 a);
static bad_forceinline f32x4 bad_veccall mask128_u32x4_to_f32x4(mask128 a);
static bad_forceinline f32x4 bad_veccall mask128_s32x4_to_f32x4(mask128 a);


#include "mask128/mask128_x86-64.inl"

BAD_NAMESPACE_END

#endif