#include "util.h"

#define _USE_MATH_DEFINES
#include <math.h>

float deg2rad(float deg) {
  return deg / 180.0f * (float)M_PI;
}

float rad2deg(float rad) {
  return rad * 180.0f / (float)M_PI;
}

Quaternion axisAngleToQuat(float angle, Vector3f axis) {
  axis = glm::normalize(axis);

  float sinAngle = sin(angle/2.0f);

  return glm::normalize( Quaternion(cos(angle/2.0f), axis.x*sinAngle, axis.y*sinAngle, axis.z*sinAngle));
}
