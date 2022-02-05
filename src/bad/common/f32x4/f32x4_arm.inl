// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any()
{
    const f32x4 v;
    
    return v;
}


static bad_forceinline f32x4 f32x4_zero()
{
    return vdupq_n_f32(.0f);
}


static bad_forceinline f32x4 f32x4_one()
{
    const mask128 one = vshlq_n_u32(vshrq_n_u32(mask128_all1(), 25), 23);

    return vreinterpretq_f32_u32(one);
}


// ========== Loads & stores ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr)
{
    return vld1q_f32(mem_addr);
}


static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr)
{
    return vld1q_f32(mem_addr);
}


static bad_forceinline f32x4 f32x4_set(f32 a, f32 b, f32 c, f32 d)
{
    const f32 v[4] = {a, b, c, d};
    
    return f32x4_load(v);
}


static bad_forceinline f32x4 f32x4_set1(f32 k)
{
    return vdupq_n_f32(k);
}


static bad_forceinline void bad_veccall f32x4_store(f32* mem_addr, f32x4_vec0 a)
{
    vst1q_f32(mem_addr, a);
}


static bad_forceinline void bad_veccall f32x4_storeu(f32* mem_addr, f32x4_vec0 a)
{
    vst1q_f32(mem_addr, a);
}


// =========== Selection ============
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask256_vec2 m)
{
    return vbslq_f32(m, a, b);
}


// ============ Conversion =============
static bad_forceinline f32x4 bad_veccall f32x4_cast_mask128(f32x4_vec0 a)
{
    return vreinterpretq_u32_f32(a);
}