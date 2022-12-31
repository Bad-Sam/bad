static bad_forceinline mat4x4 mat4x4_load(f32* coefs)
{
#if defined(__AVX__)
    return (mat4x4){{{f32x8_load(coefs), f32x8_load(coefs + 8u)}}};
#else
    return (mat4x4)
    {
        {f32x4_load(coefs), f32x4_load(coefs + 4u), f32x4_load(coefs + 8u), f32x4_load(coefs + 12u)}
    };
#endif
}


static bad_forceinline mat4x4 bad_veccall mat4x4_set_cols(f32x4 col0, f32x4 col1, f32x4 col2, f32x4 col3)
{
#if defined(__AVX__)
    return (mat4x4){{{_mm256_set_m128(col1, col0), _mm256_set_m128(col3, col2)}}};
#else
    return (mat4x4){{col0, col1, col2, col3}};
#endif
}