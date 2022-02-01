#ifndef BAD_F32X8_H
#define BAD_F32X8_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <bad/types.h>

#include "mask256.h"

BAD_NAMESPACE_START

// ============= Defaults =============
static bad_forceinline f32x8 f32x8_any();
static bad_forceinline f32x8 f32x8_zero();
static bad_forceinline f32x8 f32x8_one();


// ========== Loads & stores ==========
static bad_forceinline f32x8 f32x8_load(const f32* mem_addr);
static bad_forceinline f32x8 f32x8_loadu(const f32* mem_addr);
static bad_forceinline f32x8 f32x8_set(f32 a, f32 b, f32 c, f32 d,
                                       f32 e, f32 f, f32 g, f32 h);
static bad_forceinline f32x8 f32x8_set1(f32 a);            
static bad_forceinline void bad_veccall f32x8_store(f32* mem_addr, f32x8_vec0 a);
static bad_forceinline void bad_veccall f32x8_storeu(f32* mem_addr, f32x8_vec0 a);


// ======= Selection & tests ========
static bad_forceinline f32x8 bad_veccall f32x8_blend(f32x8_vec0 a, f32x8_vec1 b, mask256_vec2 m);


// ============ Cast/reinterpret =============
static bad_forceinline mask256 bad_veccall f32x8_cast_mask256(f32x8_vec0 a);


#if defined(__AVX__)
#   include "f32x8/f32x8_x86-64.inl"
#else
#   include "f32x8/f32x8_no_avx.inl"
#endif

BAD_NAMESPACE_END

#endif