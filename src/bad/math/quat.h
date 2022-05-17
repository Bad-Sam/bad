#ifndef BAD_QUAT_H
#define BAD_QUAT_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/math_types.h>

#include "f32x4_calc.h"
#include "f32_calc.h"
#include "vec3.h"

BAD_NAMESPACE_START

// They work exactly the same
#define quat_load   f32x4_load
#define quat_loadu  f32x4_loadu
#define quat_set    f32x4_set
#define quat_store  f32x4_store
#define quat_storeu f32x4_storeu

bad_forceinline quat        quat_identity       ();

bad_inline quat bad_veccall quat_from_axis_angle(vec3 unit_axis, f32 angle);
bad_inline quat bad_veccall quat_from_euler     (f32x4 xyz_angles);
bad_inline f32  bad_veccall quat_length_squared (quat q);
bad_inline f32  bad_veccall quat_length         (quat q);
bad_inline quat bad_veccall quat_normalize      (quat q);
bad_inline quat bad_veccall quat_inverse        (quat q);
bad_inline quat bad_veccall quat_mul            (quat q0, quat q1);
bad_inline vec3 bad_veccall quat_rot            (quat q, vec3 v);
bad_inline f32  bad_veccall quat_dot            (quat q0, quat q1);
bad_inline quat bad_veccall quat_lerp           (quat q0, quat q1, f32 t);
bad_inline quat bad_veccall quat_slerp          (quat q0, quat q1, f32 t);

#include "quat.inl"

BAD_NAMESPACE_END

#endif