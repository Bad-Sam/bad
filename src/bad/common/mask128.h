#ifndef BAD_MASK128_H
#define BAD_MASK128_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <bad/types/simd_types.h>
#include <bad/debug.h>

BAD_NAMESPACE_START

// ========== Load & store ==========
static bad_forceinline mask128 mask128_load(const mask_elem* mem_addr);
static bad_forceinline mask128 mask128_loadu(const mask_elem* mem_addr);
static bad_forceinline mask128 mask128_set(mask_elem a, mask_elem b, mask_elem c, mask_elem d);
static bad_forceinline mask128 mask128_set_all(mask_elem k);
static bad_forceinline void bad_veccall mask128_store(mask_elem* mem_addr, mask128_vec0 a);
static bad_forceinline void bad_veccall mask128_storeu(mask_elem* mem_addr, mask128_vec0 a);


// ========== Common masks ==========
static bad_forceinline mask128 mask128_zero();
static bad_forceinline mask128 mask128_all1();
static bad_forceinline mask128 mask128_value32();
static bad_forceinline mask128 mask128_highbit32();
static bad_forceinline mask128 mask128_lowbit32();
static bad_forceinline mask128 mask128_exponent32();


// ======= Masking operations =======
static bad_forceinline mask128 bad_veccall mask128_keep_highbit32(mask128_vec0 a);
static bad_forceinline mask128 bad_veccall mask128_keep_lowbit32(mask128_vec0 a);
static bad_forceinline mask128 bad_veccall mask128_shift_left32(mask128_vec0 a, s32 shift);
static bad_forceinline mask128 bad_veccall mask128_shift_right32(mask128_vec0 a, s32 shift);


// ============== Getters =============
static bad_forceinline mask_elem bad_veccall mask128_get_0(mask128_vec0 a);
static bad_forceinline mask_elem bad_veccall mask128_get_1(mask128_vec0 a);
static bad_forceinline mask_elem bad_veccall mask128_get_2(mask128_vec0 a);
static bad_forceinline mask_elem bad_veccall mask128_get_3(mask128_vec0 a);


// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 mask128_neq(mask128_vec0 a, mask128_vec1 b);


// ======= Bitwise operations =======
static bad_forceinline mask128 bad_veccall mask128_and(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_and_not(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_or(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_xor(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_not(mask128_vec0 a);


// ======== Cast & conversion =========
static bad_forceinline f32x4 bad_veccall mask128_as_f32x4(mask128_vec0 a);
static bad_forceinline f32x4 bad_veccall mask128_u32x4_to_f32x4(mask128_vec0 a);
static bad_forceinline f32x4 bad_veccall mask128_s32x4_to_f32x4(mask128_vec0 a);

#if defined(__SSE__)
#   include "mask128/mask128_x86-64.inl"
#elif defined(__ARM_NEON_FP)
#   include "mask128/mask128_arm.inl"
#else
#   include "mask128/mask128_no_simd.inl"
#endif

BAD_NAMESPACE_END

#endif