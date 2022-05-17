static bad_forceinline f32 u32_as_f32(u32 a)
{
    return *(f32*)&a;
}


static bad_forceinline u32 u32_bool_to_mask(u32 zero_or_one)
{
    return 0xFFFFFFFF * zero_or_one;
}

static bad_forceinline u32 u32_div_ceiled(u32 a, u32 b)
{
    return (a + b - 1u) / b;
}