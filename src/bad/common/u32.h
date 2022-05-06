#ifndef BAD_U32_H
#define BAD_U32_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

static bad_forceinline f32 u32_as_f32(u32 a);
static bad_forceinline u32 u32_bool_to_mask(u32 zero_or_one);

#include "u32.inl"

BAD_NAMESPACE_END

#endif