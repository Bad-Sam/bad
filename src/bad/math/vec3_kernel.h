#ifndef BAD_VEC3_KERNEL_H
#define BAD_VEC3_KERNEL_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

void vec3_ker_dot            (      f32* bad_restrict res,
                              const f32* bad_restrict a,
                              const f32* bad_restrict b,
                                    u32               vec3_count);

void vec3_ker_length_squared (      f32* bad_restrict res,
                              const f32* bad_restrict a,
                                    u32               vec3_count);

void vec3_ker_length         (      f32* bad_restrict res,
                              const f32* bad_restrict a,
                                    u32               vec3_count);

void vec3_ker_unit           (      f32* bad_restrict res,
                              const f32* bad_restrict a,
                                    u32               vec3_count);
/*
void vec3_ker_cross          (      f32* bad_restrict res,
                              const f32* bad_restrict a,
                              const f32* bad_restrict b,
                                    u32               vec3_count);

void vec3_ker_project_on     (      f32* bad_restrict res,
                              const f32* bad_restrict v,
                              const f32* bad_restrict axis,
                                    u32               vec3_count);

void vec3_ker_project_on_unit(      f32* bad_restrict res,
                              const f32* bad_restrict v,
                              const f32* bad_restrict axis,
                                    u32               vec3_count);

void vec3_ker_reflect        (      f32* bad_restrict res,
                              const f32* bad_restrict v,
                              const f32* bad_restrict unit_normal,
                                    u32               vec3_count);

void vec3_ker_rot_around_axis(      f32* bad_restrict res,
                              const f32* bad_restrict v,
                              const f32* bad_restrict unit_axis,
                              const f32* bad_restrict angle,
                                    u32               vec3_count);

void vec3_ker_lerp           (      f32* bad_restrict res,
                              const f32* bad_restrict a,
                              const f32* bad_restrict b,
                              const f32* bad_restrict t,
                                    u32               vec3_count);

*/
BAD_NAMESPACE_END

#endif
