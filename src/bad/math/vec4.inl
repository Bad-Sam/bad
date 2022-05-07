bad_inline f32 bad_veccall vec4_dot(vec4 v0, vec4 v1)
{
#if defined(__SSE4_1__)
    return f32x4_get_0(_mm_dp_ps(v0, v1, 0b11111111));
#else
    return f32x4_sum4(f32x4_mul(v0, v1));
#endif
}


bad_inline f32 bad_veccall vec4_length_squared(vec4 v0)
{
    return f32x4_sum4(f32x4_mul(v0, v0));
}


bad_inline f32 bad_veccall vec4_length(vec4 v0)
{
    f32x4 len_sqr = f32x4_mul(v0, v0);
          len_sqr = f32x4_hadd4(len_sqr);
    
    return f32x4_get_0(f32x4_sqrt(len_sqr));
}


bad_inline vec4 bad_veccall vec4_unit(vec4 v0)
{
#if defined(__SSE4_1__)
    f32x4 len = _mm_dp_ps(v0, v0, 0b11111111);
#else
    f32x4 len = f32x4_mul(v0, v0);
          len = f32x4_hadd4(len);
          len = f32x4_broadcast_0(len);
#endif
          len = f32x4_rsqrt(len);

    return f32x4_mul(v0, len);
}


bad_inline vec4 bad_veccall vec4_lerp(vec4 v0, vec4 v1, f32 t)
{
    return f32x4_lerp(v0, v1, f32x4_set_all(t));
}