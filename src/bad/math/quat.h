#ifndef BAD_QUAT_H
#define BAD_QUAT_H

#include <bad/bad.h>
#include <bad/args.h>
#include <bad/qualifiers.h>

#include "f32x4_calc.h"
#include "f32_calc.h"
#include "vec3.h"

BAD_NAMESPACE_START

typedef f32x4 quat;

// They work exactly the same
#define quat_load   f32x4_load
#define quat_loadu  f32x4_loadu
#define quat_set    f32x4_set
#define quat_store  f32x4_store
#define quat_storeu f32x4_storeu

bad_forceinline quat        quat_identity       ();

bad_inline quat bad_veccall quat_from_axis_angle(f32x4_vec0 unit_axis, f32 angle);
bad_inline quat bad_veccall quat_from_euler     (f32x4_vec0 xyz_angles);
bad_inline quat bad_veccall quat_conjugate      (f32x4_vec0 q);
bad_inline quat bad_veccall quat_mul            (f32x4_vec0 q0, f32x4_vec1 q1);
bad_inline vec3 bad_veccall quat_rot            (f32x4_vec0 q, f32x4_vec1 v);
bad_inline f32  bad_veccall quat_dot            (f32x4_vec0 q0, f32x4_vec1 q1);

#include "quat.inl"

BAD_NAMESPACE_END

#endif