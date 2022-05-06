#ifndef BAD_VEC3_H
#define BAD_VEC3_H

#include <bad/args.h>
#include <bad/types/math_types.h>
#include <bad/qualifiers.h>

#include <bad/math/f32x4_calc.h>
#include <bad/debug.h>

BAD_NAMESPACE_START

typedef f32x4 vec3;

static bad_forceinline vec3             vec3_load (const f32* mem_addr);
static bad_forceinline vec3             vec3_set  (f32 x, f32 y, f32 z);
static bad_forceinline void bad_veccall vec3_store(f32* mem_addr, f32x4_vec0 a);

bad_inline f32  bad_veccall vec3_dot            (f32x4_vec0 v0, f32x4_vec1 v1);
bad_inline f32  bad_veccall vec3_length_squared (f32x4_vec1 v);
bad_inline f32  bad_veccall vec3_length         (f32x4_vec1 v);
bad_inline vec3 bad_veccall vec3_unit           (f32x4_vec0 v);
bad_inline vec3 bad_veccall vec3_cross          (f32x4_vec0 v0, f32x4_vec1 v1);
bad_inline vec3 bad_veccall vec3_project_on     (f32x4_vec0 v, f32x4_vec1 axis);
bad_inline vec3 bad_veccall vec3_project_on_unit(f32x4_vec0 v, f32x4_vec1 axis);
bad_inline vec3 bad_veccall vec3_reflect        (f32x4_vec0 v, f32x4_vec1 unit_normal);
bad_inline vec3 bad_veccall vec3_rot_around_axis(f32x4_vec0 v, f32x4_vec1 unit_axis, f32 angle);
bad_inline vec3 bad_veccall vec3_lerp           (f32x4_vec1 v0, f32x4_vec1 v1, f32 t);


#include "vec3.inl"

BAD_NAMESPACE_END

#endif