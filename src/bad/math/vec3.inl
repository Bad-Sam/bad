static bad_forceinline vec3 vec3_load(const f32* mem_addr)
{
    bad_assert(mem_addr != NULL);

    return vec3_set(mem_addr[0], mem_addr[1], mem_addr[2]);
}


static bad_forceinline vec3 vec3_set(f32 x, f32 y, f32 z)
{
    bad_align(16) f32 elem[4] = {x, y, z, .0f};

    return f32x4_load(elem);
}


static bad_forceinline void bad_veccall vec3_store(f32* mem_addr, vec3 a)
{
    bad_assert(mem_addr != NULL);

    bad_align(16) f32 store[4];
    f32x4_store(store, a);

    mem_addr[0] = store[0];
    mem_addr[1] = store[1];
    mem_addr[2] = store[2];
}


// (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z)
bad_inline f32 bad_veccall vec3_dot(vec3 v0, vec3 v1)
{
#if defined(__SSE4_1__)
    return f32x4_get_0(_mm_dp_ps(v0, v1, 0b01110111));
#else
    return f32x4_sum3(f32x4_mul(v0, v1));
#endif
}


// ||v||² = x² + y² + z²
bad_inline f32 bad_veccall vec3_length_squared(vec3 v)
{
    return vec3_dot(v, v);
}


// ||v|| = sqrt(x² + y² + z²)
bad_inline f32 bad_veccall vec3_length(vec3 v)
{
#if defined(__SSE4_1__)
    f32x4 len_sqr = _mm_dp_ps(v, v, 0b01110111);
#else
    f32x4 len_sqr = f32x4_mul(v, v);
          len_sqr = f32x4_hadd3(len_sqr);
#endif
    
    return f32x4_get_0(f32x4_sqrt(len_sqr));
}


// v / ||v||
bad_inline vec3 bad_veccall vec3_unit(vec3 v)
{
    bad_assert(vec3_length_squared(v) != .0f);
    
#if defined(__SSE4_1__)
    f32x4 len2 = _mm_dp_ps(v, v, 0b01110111);
#else
    f32x4 len2 = f32x4_mul(v, v);
          len2 = f32x4_hadd3(len2);
          len2 = f32x4_broadcast_0(len2);
#endif

#if defined(__SSE__)
    f32x4 len_rcp = _mm_rsqrt_ss(len2);
#else
    f32x4 len_rcp = f32x4_rsqrt(len2);
#endif

    return f32x4_mul(v, len_rcp);
}


// [(v0.y * v1.z) - (v0.z * v1.y),
//  (v0.z * v1.x) - (v0.x * v1.z),
//  (v0.x * v1.y) - (v0.y * v1.x)]
bad_inline vec3 bad_veccall vec3_cross(vec3 v0, vec3 v1)
{
#if defined(__SSE__)
    vec3 v0_yzxw = _mm_shuffle_ps(v0, v0, _MM_SHUFFLE(3, 0, 2, 1));
    vec3 v1_yzxw = _mm_shuffle_ps(v1, v1, _MM_SHUFFLE(3, 0, 2, 1));

    vec3 cross = f32x4_mul(v1, v0_yzxw);
         cross = f32x4_mul_sub(v0, v1_yzxw, cross);
    
    return _mm_shuffle_ps(cross, cross, _MM_SHUFFLE(3, 0, 2, 1));
#else
    f32 v0_x = f32x4_get_0(v0);
    f32 v0_y = f32x4_get_1(v0);
    f32 v0_z = f32x4_get_2(v0);
    f32 v1_x = f32x4_get_0(v1);
    f32 v1_y = f32x4_get_1(v1);
    f32 v1_z = f32x4_get_2(v1);

    return f32x4_set(v0_y * v1_z - v0_z * v1_y,
                     v0_z * v1_x - v0_x * v1_z,
                     v0_x * v1_y - v0_y * v1_x,
                     .0f);
#endif
}


// (dot(v, axis) / ||axis||²) * axis
bad_inline vec3 bad_veccall vec3_project_on(vec3 v, vec3 axis)
{
#if defined(__SSE4_1__)
    f32x4 dot       = _mm_dp_ps(v, axis, 0b01110111);
    f32x4 axis_len2 = _mm_dp_ps(axis, axis, 0b01110111);

    f32x4 proj = _mm_div_ss(dot, axis_len2);
#else
    f32x4 dot       = f32x4_hadd3(f32x4_mul(v, axis));
    f32x4 axis_len2 = f32x4_hadd3(f32x4_mul(axis, axis));

    bad_assert(f32x4_get_0(axis_len2) != .0f);

#   if defined(__SSE__)
    f32x4 proj = _mm_div_ss(dot, axis_len2);
#   else
    f32x4 proj = f32x4_div(dot, axis_len2);
#   endif
          proj = f32x4_broadcast_0(proj);
#endif

    return f32x4_mul(proj, axis);
}


// dot(v, unit_axis) * unit_axis
bad_inline vec3 bad_veccall vec3_project_on_unit(vec3 v, vec3 unit_axis)
{
#if defined(__SSE4_1__)
    f32x4 dot = _mm_dp_ps(v, unit_axis, 0b01110111);
#else
    f32x4 dot = f32x4_hadd3(f32x4_mul(v, unit_axis));
          dot = f32x4_broadcast_0(dot);
#endif

    // Apply projection
    return f32x4_mul(dot, unit_axis);
}


// v - 2 * dot(v, unit_normal) * unit_normal
bad_inline vec3 bad_veccall vec3_reflect(vec3 v, vec3 unit_normal)
{
#if defined(__SSE4_1__)
    f32x4 dot = _mm_dp_ps(v, unit_normal, 0b01110111);
#else
    f32x4 dot = f32x4_hadd3(f32x4_mul(v, unit_normal));
#endif

#if defined(__SSE2__)
    f32x4 two = f32x4_two();
#else
    f32x4 two = f32x4_set_lower(2.f);
#endif
    // 2 * dot(v, unit_normal)
    f32x4 offset = f32x4_mul(two, dot);
          offset = f32x4_broadcast_0(offset);
    
    // v - offset * unit_normal
    return f32x4_nmul_add(offset, unit_normal, v);
}


// Rodrigues' rotation
// v * cos(angle) + cross(unit_axis, v) * sin(angle) + unit_axis * dot(unit_axis, v) * (1 - cos(angle))
bad_inline vec3 bad_veccall vec3_rot_around_axis(vec3 v, vec3 unit_axis, f32 angle)
{
#if defined(__SSE4_1__)
    f32x4 axis_dot_v = _mm_dp_ps(v, unit_axis, 0b01110111);
#else
    f32x4 axis_dot_v = f32x4_hadd3(f32x4_mul(v, unit_axis));
          axis_dot_v = f32x4_broadcast_0(axis_dot_v);
#endif

    f32x4 cos_angle = f32x4_set_all(f32_cos(angle));
    f32x4 sin_angle = f32x4_set_all(f32_sin(angle));
    f32x4 one       = f32x4_one();
    f32x4 last_comp = f32x4_mul(axis_dot_v, f32x4_sub(one, cos_angle));

    vec3  cross = vec3_cross(unit_axis, v);
    vec3  res   = f32x4_mul(v, cos_angle);
          res   = f32x4_mul_add(cross, sin_angle, res);
          res   = f32x4_mul_add(last_comp, unit_axis, res);

    return res;
}


// v0 * (1 - t) + v1 * t
bad_inline vec3 bad_veccall vec3_lerp(vec3 v0, vec3 v1, f32 t)
{
    return f32x4_lerp(v0, v1, f32x4_set_all(t));
}