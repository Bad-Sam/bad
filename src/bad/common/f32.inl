static bad_forceinline f32 f32_blend(f32 a, f32 b, u32 m)
{
    u32 a_bits = f32_as_u32(a);
    u32 b_bits = f32_as_u32(b);

    u32 blend = (a_bits & m) | (b_bits & ~m);

    return *(f32*)&blend;
}


static bad_forceinline u32 f32_as_u32(f32 a)
{
    return *(u32*)&a;
}