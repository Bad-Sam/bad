#ifndef BAD_VEC4_H
#define BAD_VEC4_H

#include <bad/debug.h>
#include <bad/qualifiers.h>
#include <bad/math/f32x4_calc.h>
#include <bad/types/math_types.h>

BAD_NAMESPACE_START

bad_inline f32  bad_veccall vec4_dot           (vec4 v0, vec4 v1);
bad_inline f32  bad_veccall vec4_length_squared(vec4 v0);
bad_inline f32  bad_veccall vec4_length        (vec4 v0);
bad_inline vec4 bad_veccall vec4_unit          (vec4 v0);
bad_inline vec4 bad_veccall vec4_lerp          (vec4 v0, vec4 v1, f32 t);

#include "vec4.inl"

BAD_NAMESPACE_END

#endif