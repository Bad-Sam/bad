// [(0, 0, 0), 1]
bad_forceinline quat quat_identity()
{
    bad_align(16) const f32 identity[4] = {.0f, .0f, .0f, 1.f};

    return f32x4_load(identity);
}


// axis_angle = (x, y, z, angle)
bad_inline quat quat_from_axis_angle(f32x4_vec0 unit_axis, f32 angle)
{
    // Compute cos(angle * 0.5) and sin(angle * 0.5)
    f32x4 half       = f32x4_half();
    f32x4 half_angle = f32x4_set_all(angle);
          half_angle = f32x4_mul(half_angle, half);
    f32x4 sin_angle  = f32x4_sin(half_angle);
    f32x4 cos_angle  = f32x4_cos(half_angle);

    // Apply to axis
    f32x4 q = f32x4_mul(unit_axis, sin_angle);

    return f32x4_copy_3(q, cos_angle);
}


bad_inline quat quat_conjugate(f32x4_vec0 q)
{
    // TODO: compare performance with mask128_all1() and bitshifts
    mask128 conj_mask = mask128_set(0x80000000, 0x80000000, 0x80000000, 0x00000000);
    mask128 conjugate = mask128_xor(f32x4_as_mask128(q), conj_mask);

    return mask128_as_f32x4(conjugate);
}

// xyz = (q1.w * q0.xyz) + (q0.w * q1.xyz) + vec3_cross(q0.xyz, q1.xyz)
// w   = (q0.w * q1.w) - vec3_dot(q0.axis, q1.axis)
bad_inline quat bad_veccall quat_mul(f32x4_vec0 q0, f32x4_vec1 q1)
{
    vec3  new_axis = vec3_cross(q0, q1);

#if defined(__SSE4_1__)
    f32x4 dot3     = _mm_dp_ps(q0, q1, 0b01111111);
#   else
    f32x4 dot3     = f32x4_hadd3(f32x4_mul(q0, q1));
#endif

    f32x4 q0_w     = f32x4_broadcast_3(q0); 
    f32x4 q1_w     = f32x4_broadcast_3(q1);
          new_axis = f32x4_mul_add(q0_w, q1, new_axis);
          new_axis = f32x4_mul_add(q1_w, q0, new_axis);
    f32x4 new_w    = f32x4_mul_sub(q0_w, q1_w, dot3);

    return f32x4_copy_3(new_axis, new_w);
}


// 2.f * (v * (q.w² - 0.5) + (q.axis * dot(q.axis, v)) + (cross(q.axis, v) * q.w))
bad_inline vec3 bad_veccall quat_rot(f32x4_vec0 q, f32x4_vec1 v)
{
// dot(q.axis, v)
#if defined(__SSE4_1__)
    f32x4 dot3 = _mm_dp_ps(q, v, 0b01110111);
#   else
    f32x4 dot3 = f32x4_hadd3(f32x4_mul(q, v));
#endif
    // cross = cross(q.axis, v)
    f32x4 cross = vec3_cross(q, v);
    // q_w = (q.w, q.w, q.w, q.w)
    f32x4 q_w  = f32x4_broadcast_3(q);
    // q_w2 = (q.w², q.w², q.w², q.w²)
    f32x4 q_w2 = f32x4_mul(q_w, q_w);
    // one = (1, 1, 1, 1)
    f32x4 half = f32x4_half();
    // two = (2, 2, 2, 2)
    f32x4 two  = f32x4_two();

    // res = (q.w² - 1, q.w² - 1, q.w² - 1, q.w² - 1)
    f32x4 res = f32x4_sub(q_w2, half);
    // res = (v.x * (q.w² - 1), v.y * (q.w² - 1), v.z * (q.w² - 1), 0)
          res = f32x4_mul(v, res);
    // res = (v.x * (q.w² - 1), v.y * (q.w² - 1), v.z * (q.w² - 1), 0)
          res = f32x4_mul_add(q, dot3, res);
          res = f32x4_mul_add(cross, q_w, res);

    return f32x4_mul(two, res);
}