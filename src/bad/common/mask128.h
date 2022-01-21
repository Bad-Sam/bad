#ifndef BAD_MASK128_H
#define BAD_MASK128_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <bad/types.h>
#include <bad/debug.h>

BAD_NAMESPACE_START

// TODO: set, set1, any, zero
// ========== Load & store ==========
static bad_forceinline mask128 mask128_load(const mask_elem* mem_addr);
static bad_forceinline mask128 mask128_loadu(const mask_elem* mem_addr);
static bad_forceinline mask128 mask128_set(const mask_elem a, const mask_elem b,
                                           const mask_elem c, const mask_elem d);
static bad_forceinline mask128 mask128_set1(const mask_elem k);
static bad_forceinline void bad_veccall mask128_store(mask_elem* const mem_addr, mask128_vec0 a);
static bad_forceinline void bad_veccall mask128_storeu(mask_elem* const mem_addr, mask128_vec0 a);


// ========== Common masks ==========
static bad_forceinline mask128 mask128_zero();
static bad_forceinline mask128 mask128_all1();
static bad_forceinline mask128 mask128_value32();
static bad_forceinline mask128 mask128_highbit32();
static bad_forceinline mask128 mask128_lowbit32();
static bad_forceinline mask128 mask128_exponent32();


// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 mask128_neq(mask128_vec0 a, mask128_vec1 b);


// ======= Bitwise operations =======
static bad_forceinline mask128 bad_veccall mask128_and(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_and_not(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_or(mask128_vec0 a, mask128_vec1 b);
static bad_forceinline mask128 bad_veccall mask128_xor(mask128_vec0 a, mask128_vec1 b);


// ============ Conversion =============
static bad_forceinline f32x4 bad_veccall mask128_cast_f32x4(mask128_vec0 a);

#if defined(__SSE__)
#   include "mask128/mask128_x86-64.inl"
#elif defined(__ARM_NEON)
#   include "mask128/mask128_arm.inl"
#else
#   include "mask128/mask128_nosimd.inl"
#endif

BAD_NAMESPACE_END

#endif