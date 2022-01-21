static bad_inline f32 bad_veccall vec4_dot(vec4_vec0 v0, vec4_vec1 v1)
{
#if defined(__SSE4_1__)
    return _mm_cvtss_f32(_mm_dp_ps(v0, v1, 0xFFFFFFFF));
#else
    return f32x4_hadd(f32x4_mul(v0, v1));
#endif
}

/*
// dot[i] = v0[i] . v1[i]
inline void bad_veccall vec4_dotn(f32* const dot,
                                                  const vec4* const bad_restrict v0,
                                                  const vec4* const bad_restrict v1,
                                                  const u32 n)
{
#if defined(__SSE__)
    // Prevent an overwrite in dot
    u32 i = 0u;
    for (; i + 4u < n; i += 4u)
    {
        // v0[i + n] = (x, y, z, w)
        __m128 v0x = v0[i];
        __m128 v0y = v0[i + 1u];
        __m128 v0z = v0[i + 2u];
        __m128 v0w = v0[i + 3u];

        // v0[i + n]   = (x, x, x, x)
        // v0[i + n+1] = (y, y, y, y)
        // ...
        _MM_TRANSPOSE4_PS(v0x, v0y, v0z, v0w);
        
        // v1[i + n] = (x, y, z, w)
        __m128 v1x = v1[i];
        __m128 v1y = v1[i + 1u];
        __m128 v1z = v1[i + 2u];
        __m128 v1w = v1[i + 3u];

        // v1[i + n]   = (x, x, x, x)
        // v1[i + n+1] = (y, y, y, y)
        // ...
        _MM_TRANSPOSE4_PS(v1x, v1y, v1z, v1w);

        __m128 res = _mm_mul_ps(v0x, v1x);
        res        = _mm_add_ps(res, _mm_mul_ps(v0y, v1y));
        res        = _mm_add_ps(res, _mm_mul_ps(v0z, v1z));
        res        = _mm_add_ps(res, _mm_mul_ps(v0w, v1w));

        _mm_store_ps(dot + i, res);
    }

    for (; i < n; i++)
    {
        dot[i] = vec4_dot(v0[i], v1[i]);
    }
#else
    for (u32 i = 0u; i < n; i++)
    {
        dot[i] = vec4_dot(v0[i], v1[i]);
    }
#endif
}
*/