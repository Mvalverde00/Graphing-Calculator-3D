#ifndef __MATH_UTIL_H__
#define __MATH_UTIL_H__

#include "vectors.h"

float deg2rad(float deg);

float rad2deg(float rad);

Quaternion axisAngleToQuat(float angle, Vector3f axis);

#endif
