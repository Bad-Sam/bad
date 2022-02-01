#ifndef BAD_MASK256_H
#define BAD_MASK256_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <bad/types.h>
#include <bad/debug.h>

#if !defined(__AVX__)
#   include "mask128.h"
#endif

BAD_NAMESPACE_START

// ========== Load & store ==========
static bad_forceinline mask256 mask256_load(const mask_elem* mem_addr);
static bad_forceinline mask256 mask256_loadu(const mask_elem* mem_addr);
static bad_forceinline mask256 mask256_set(mask_elem a, mask_elem b, mask_elem c, mask_elem d,
                                           mask_elem e, mask_elem f, mask_elem g, mask_elem h);
static bad_forceinline mask256 mask256_set1(mask_elem k);
static bad_forceinline void bad_veccall mask256_store(mask_elem* mem_addr, mask256_vec0 a);
static bad_forceinline void bad_veccall mask256_storeu(mask_elem* mem_addr, mask256_vec0 a);


// ========== Common masks ==========
static bad_forceinline mask256 mask256_zero();
static bad_forceinline mask256 mask256_all1();
static bad_forceinline mask256 mask256_value32();
static bad_forceinline mask256 mask256_highbit32();
static bad_forceinline mask256 mask256_lowbit32();
static bad_forceinline mask256 mask256_exponent32();


// ========== Comparison ==========
static bad_forceinline mask256 mask256_eq(mask256_vec0 a, mask256_vec1 b);
static bad_forceinline mask256 mask256_neq(mask256_vec0 a, mask256_vec1 b);


// ======= Bitwise operations =======
static bad_forceinline mask256 bad_veccall mask256_and(mask256_vec0 a, mask256_vec1 b);
static bad_forceinline mask256 bad_veccall mask256_and_not(mask256_vec0 a, mask256_vec1 b);
static bad_forceinline mask256 bad_veccall mask256_or(mask256_vec0 a, mask256_vec1 b);
static bad_forceinline mask256 bad_veccall mask256_xor(mask256_vec0 a, mask256_vec1 b);
static bad_forceinline mask256 bad_veccall mask256_not(mask256_vec0 a);


// ============ Conversion =============
static bad_forceinline f32x8 bad_veccall mask256_cast_f32x8(mask256_vec0 a);

#if defined(__AVX__)
#   include "mask256/mask256_avx.inl"
#else
#   include "mask256/mask256_no_avx.inl"
#endif

BAD_NAMESPACE_END

#endif