#include "mat4x4.h"

BAD_NAMESPACE_START

mat4x4 bad_veccall mat4x4_transpose(mat4x4 a)
{
    f32x4 tmp0 = _mm_unpacklo_ps(a.cols[0], a.cols[1]);
    f32x4 tmp2 = _mm_unpacklo_ps(a.cols[2], a.cols[3]);
    f32x4 tmp1 = _mm_unpackhi_ps(a.cols[0], a.cols[1]);
    f32x4 tmp3 = _mm_unpackhi_ps(a.cols[2], a.cols[3]);

    a.cols[0] = _mm_movelh_ps(tmp0, tmp2);
    a.cols[1] = _mm_movehl_ps(tmp2, tmp0);
    a.cols[2] = _mm_movelh_ps(tmp1, tmp3);
    a.cols[3] = _mm_movehl_ps(tmp3, tmp1);

    return a;
}


mat4x4 bad_veccall mat4x4_mul(mat4x4 a, mat4x4 b)
{
    mat4x4 res;

#if defined(__AVX__)
        // res[0] = a[0] * b[0].x + a[1] * b[0].y + a[2] * b[0].z + a[3] * b[0].w
        // res[1] = a[0] * b[1].x + a[1] * b[1].y + a[2] * b[1].z + a[3] * b[1].w
        __m256 tmp       = _mm256_permute_ps(b.cols_by_2[0], 0b00000000);
        __m256 a0        = _mm256_broadcast_ps(&a.cols[0]);
        res.cols_by_2[0] = _mm256_mul_ps(a0, tmp);
        tmp              = _mm256_permute_ps(b.cols_by_2[0], 0b01010101);
        __m256 a1        = _mm256_broadcast_ps(&a.cols[1]);
        res.cols_by_2[0] = _mm256_fmadd_ps(a1, tmp, res.cols_by_2[0]);
        tmp              = _mm256_permute_ps(b.cols_by_2[0], 0b10101010);
        __m256 a2        = _mm256_broadcast_ps(&a.cols[2]);
        res.cols_by_2[0] = _mm256_fmadd_ps(a2, tmp, res.cols_by_2[0]);
        tmp              = _mm256_permute_ps(b.cols_by_2[0], 0b11111111);
        __m256 a3        = _mm256_broadcast_ps(&a.cols[3]);
        res.cols_by_2[0] = _mm256_fmadd_ps(a3, tmp, res.cols_by_2[0]);

        // res[2] = a[0] * b[2].x + a[1] * b[2].y + a[2] * b[2].z + a[3] * b[2].w
        // res[3] = a[0] * b[3].x + a[1] * b[3].y + a[2] * b[3].z + a[3] * b[3].w
        tmp              = _mm256_permute_ps(b.cols_by_2[0], 0b00000000);
        res.cols_by_2[1] = _mm256_mul_ps(a0, tmp);
        tmp              = _mm256_permute_ps(b.cols_by_2[1], 0b01010101);
        res.cols_by_2[1] = _mm256_fmadd_ps(a1, tmp, res.cols_by_2[1]);
        tmp              = _mm256_permute_ps(b.cols_by_2[1], 0b10101010);
        res.cols_by_2[1] = _mm256_fmadd_ps(a2, tmp, res.cols_by_2[1]);
        tmp              = _mm256_permute_ps(b.cols_by_2[1], 0b11111111);
        res.cols_by_2[1] = _mm256_fmadd_ps(a3, tmp, res.cols_by_2[1]);
#else
        // res[0] = a[0] * b[0].x + a[1] * b[0].y + a[2] * b[0].z + a[3] * b[0].w
        __m128 tmp  = _mm_shuffle_ps(b.cols[0], b.cols[0], _MM_SHUFFLE(0, 0, 0, 0));
        res.cols[0] = _mm_mul_ps(a.cols[0], tmp);
        tmp         = _mm_shuffle_ps(b.cols[0], b.cols[0], _MM_SHUFFLE(1, 1, 1, 1));
        res.cols[0] = _mm_fmadd_ps(a.cols[1], tmp, res.cols[0]);
        tmp         = _mm_shuffle_ps(b.cols[0], b.cols[0], _MM_SHUFFLE(2, 2, 2, 2));
        res.cols[0] = _mm_fmadd_ps(a.cols[2], tmp, res.cols[0]);
        tmp         = _mm_shuffle_ps(b.cols[0], b.cols[0], _MM_SHUFFLE(3, 3, 3, 3));
        res.cols[0] = _mm_fmadd_ps(a.cols[3], tmp, res.cols[0]);

        // res[1] = a[0] * b[1].x + a[1] * b[1].y + a[2] * b[1].z + a[3] * b[1].w
        tmp         = _mm_shuffle_ps(b.cols[1], b.cols[1], _MM_SHUFFLE(0, 0, 0, 0));
        res.cols[1] = _mm_mul_ps(a.cols[0], tmp);
        tmp         = _mm_shuffle_ps(b.cols[1], b.cols[1], _MM_SHUFFLE(1, 1, 1, 1));
        res.cols[1] = _mm_fmadd_ps(a.cols[1], tmp, res.cols[1]);
        tmp         = _mm_shuffle_ps(b.cols[1], b.cols[1], _MM_SHUFFLE(2, 2, 2, 2));
        res.cols[1] = _mm_fmadd_ps(a.cols[2], tmp, res.cols[1]);
        tmp         = _mm_shuffle_ps(b.cols[1], b.cols[1], _MM_SHUFFLE(3, 3, 3, 3));
        res.cols[1] = _mm_fmadd_ps(a.cols[3], tmp, res.cols[1]);

        // res[2] = a[0] * b[2].x + a[1] * b[2].y + a[2] * b[2].z + a[3] * b[2].w
        tmp         = _mm_shuffle_ps(b.cols[2], b.cols[2], _MM_SHUFFLE(0, 0, 0, 0));
        res.cols[2] = _mm_mul_ps(a.cols[0], tmp);
        tmp         = _mm_shuffle_ps(b.cols[2], b.cols[2], _MM_SHUFFLE(1, 1, 1, 1));
        res.cols[2] = _mm_fmadd_ps(a.cols[1], tmp, res.cols[2]);
        tmp         = _mm_shuffle_ps(b.cols[2], b.cols[2], _MM_SHUFFLE(2, 2, 2, 2));
        res.cols[2] = _mm_fmadd_ps(a.cols[2], tmp, res.cols[2]);
        tmp         = _mm_shuffle_ps(b.cols[2], b.cols[2], _MM_SHUFFLE(3, 3, 3, 3));
        res.cols[2] = _mm_fmadd_ps(a.cols[3], tmp, res.cols[2]);

        // res[3] = a[0] * b[3].x + a[1] * b[3].y + a[2] * b[3].z + a[3] * b[3].w
        tmp         = _mm_shuffle_ps(b.cols[3], b.cols[3], _MM_SHUFFLE(0, 0, 0, 0));
        res.cols[3] = _mm_mul_ps(a.cols[0], tmp);
        tmp         = _mm_shuffle_ps(b.cols[3], b.cols[3], _MM_SHUFFLE(1, 1, 1, 1));
        res.cols[3] = _mm_fmadd_ps(a.cols[1], tmp, res.cols[3]);
        tmp         = _mm_shuffle_ps(b.cols[3], b.cols[3], _MM_SHUFFLE(2, 2, 2, 2));
        res.cols[3] = _mm_fmadd_ps(a.cols[2], tmp, res.cols[3]);
        tmp         = _mm_shuffle_ps(b.cols[3], b.cols[3], _MM_SHUFFLE(3, 3, 3, 3));
        res.cols[3] = _mm_fmadd_ps(a.cols[3], tmp, res.cols[3]);
#endif

    return res;
}

BAD_NAMESPACE_END