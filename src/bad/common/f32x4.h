#ifndef BAD_F32X4_H
#define BAD_F32X4_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <bad/types.h>

#include "mask128.h"

BAD_NAMESPACE_START

// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any();
static bad_forceinline f32x4 f32x4_zero();
static bad_forceinline f32x4 f32x4_one();


// ========== Loads & stores ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr);
static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr);
static bad_forceinline f32x4 f32x4_set(f32 a, f32 b, f32 c, f32 d);
static bad_forceinline f32x4 f32x4_set1(f32 k);
static bad_forceinline void bad_veccall f32x4_store(f32* mem_addr, f32x4_vec0 a);
static bad_forceinline void bad_veccall f32x4_storeu(f32* mem_addr, f32x4_vec0 a);


// ======= Selection & tests ========
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask128_vec2 m);


// ============ Cast/reinterpret =============
static bad_forceinline mask128 bad_veccall f32x4_cast_mask128(f32x4_vec0 a);


#if defined(__SSE__)
#   include "f32x4/f32x4_x86-64.inl"
#elif defined(__ARM_NEON_FP)
#   include "f32x4/f32x4_arm.inl"
#else
#   include "f32x4/f32x4_no_simd.inl"
#endif

BAD_NAMESPACE_END

#endif