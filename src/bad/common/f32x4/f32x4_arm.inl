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


static bad_forceinline f32x4 f32x4_half()
{
    mask128 all1_mask = mask128_all1();
    mask128 half      = vshrq_n_u32(vshlq_n_u32(all1_mask, 26), 2);

    return vreinterpretq_f32_u32(half);
}


static bad_forceinline f32x4 f32x4_one()
{
    mask128 all1_mask = mask128_all1();
    mask128 one       = vshrq_n_u32(vshlq_n_u32(all1_mask, 25), 2);

    return vreinterpretq_f32_u32(one);
}


static bad_forceinline f32x4 f32x4_two()
{
    mask128 all1_mask = mask128_all1();
    mask128 two       = vshrq_n_u32(vshlq_n_u32(all1_mask, 31), 1);

    return vreinterpretq_f32_u32(two);
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


static bad_forceinline f32x4 f32x4_set_all(f32 a)
{
    return vdupq_n_f32(a);
}


static bad_forceinline f32x4 f32x4_set_lower(f32 a)
{
    return f32x4_set(a, .0f, .0f, .0f);
}


static bad_forceinline void f32x4_store(f32* mem_addr, f32x4 a)
{
    vst1q_f32(mem_addr, a);
}


static bad_forceinline void f32x4_storeu(f32* mem_addr, f32x4 a)
{
    vst1q_f32(mem_addr, a);
}


static bad_forceinline void bad_veccall f32x4_store_lower(f32* mem_addr, f32x4 a)
{
    mem_addr[0] = f32x4_get_0(a);
}


// ============== Getter ==============
static bad_forceinline f32 f32x4_get_0(f32x4 a)
{
    return vgetq_lane_f32(a, 0);
}


static bad_forceinline f32 f32x4_get_1(f32x4 a)
{
    return vgetq_lane_f32(a, 1);
}


static bad_forceinline f32 f32x4_get_2(f32x4 a)
{
    return vgetq_lane_f32(a, 2);
}


static bad_forceinline f32 f32x4_get_3(f32x4 a)
{
    return vgetq_lane_f32(a, 3);
}


// ============== Setters =============
static bad_forceinline f32x4 bad_veccall f32x4_copy_0(f32x4 a, f32x4 origin)
{
    return vcopyq_laneq_f32(a, 0, origin, 0);
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_1(f32x4 a, f32x4 origin)
{
    return vcopyq_laneq_f32(a, 1, origin, 1);
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_2(f32x4 a, f32x4 origin)
{
    return vcopyq_laneq_f32(a, 2, origin, 2);
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_3(f32x4 a, f32x4 origin)
{
    return vcopyq_laneq_f32(a, 3, origin, 3);
}


static bad_forceinline f32x4 bad_veccall f32x4_set_0(f32x4 a, f32 value)
{
    return vsetq_lane_f32(value, a, 0);
}


static bad_forceinline f32x4 bad_veccall f32x4_set_1(f32x4 a, f32 value)
{
    return vsetq_lane_f32(value, a, 1);
}


static bad_forceinline f32x4 bad_veccall f32x4_set_2(f32x4 a, f32 value)
{
    return vsetq_lane_f32(value, a, 2);
}


static bad_forceinline f32x4 bad_veccall f32x4_set_3(f32x4 a, f32 value)
{
    return vsetq_lane_f32(value, a, 3);
}


// ==== Vector element broadcast =====
static bad_forceinline f32x4 bad_veccall f32x4_broadcast_0(f32x4 a)
{
    return vdupq_laneq_f32(a, 0);
}


static bad_forceinline f32x4 bad_veccall f32x4_broadcast_1(f32x4 a)
{
    return vdupq_laneq_f32(a, 1);
}


static bad_forceinline f32x4 bad_veccall f32x4_broadcast_2(f32x4 a)
{
    return vdupq_laneq_f32(a, 2);
}


static bad_forceinline f32x4 bad_veccall f32x4_broadcast_3(f32x4 a)
{
    return vdupq_laneq_f32(a, 3);
}


// =========== Selection ============
static bad_forceinline f32x4 f32x4_blend(f32x4 a, f32x4 b, mask256 m)
{
    return vbslq_f32(m, a, b);
}


// ============ Conversion =============
static bad_forceinline f32x4 f32x4_as_mask128(f32x4 a)
{
    return vreinterpretq_u32_f32(a);
}


static bad_forceinline mask128 bad_veccall f32x4_to_s32x4(f32x4 a)
{
    return vcvtq_s32_f32(a);
}


static bad_forceinline mask128 bad_veccall f32x4_to_u32x4(f32x4 a)
{
    return vcvtq_u32_f32(a);
}