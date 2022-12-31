#ifndef BAD_TRANSFORM_H
#define BAD_TRANSFORM_H

typedef struct
{
    vec3 pos;
    vec3 angle;
    vec3 c;
} transform_vec3x3;

typedef struct
{
    quat rot;
} transform_quat_vec3x2;

#endif