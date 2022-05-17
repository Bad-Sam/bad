#ifndef BAD_VEC3_H
#define BAD_VEC3_H

#include <bad/types/math_types.h>
#include <bad/qualifiers.h>

#include <bad/math/f32x4_calc.h>
#include <bad/math/f32_calc.h>
#include <bad/debug_checks.h>

BAD_NAMESPACE_START

typedef f32x4 vec3;

static bad_forceinline vec3             vec3_load (const f32* mem_addr);
static bad_forceinline vec3             vec3_set  (f32 x, f32 y, f32 z);
static bad_forceinline void bad_veccall vec3_store(f32* mem_addr, vec3 a);

bad_inline f32  bad_veccall vec3_dot            (vec3 v0, vec3 v1);
bad_inline f32  bad_veccall vec3_length_squared (vec3 v);
bad_inline f32  bad_veccall vec3_length         (vec3 v);
bad_inline vec3 bad_veccall vec3_unit           (vec3 v);
bad_inline vec3 bad_veccall vec3_cross          (vec3 v0, vec3 v1);
bad_inline vec3 bad_veccall vec3_project_on     (vec3 v, vec3 axis);
bad_inline vec3 bad_veccall vec3_project_on_unit(vec3 v, vec3 axis);
bad_inline vec3 bad_veccall vec3_reflect        (vec3 v, vec3 unit_normal);
bad_inline vec3 bad_veccall vec3_rot_around_axis(vec3 v, vec3 unit_axis, f32 angle);
bad_inline vec3 bad_veccall vec3_lerp           (vec3 v0, vec3 v1, f32 t);


#include "vec3.inl"

BAD_NAMESPACE_END

#endif