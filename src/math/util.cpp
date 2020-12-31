#include "util.h"


float deg2rad(float deg) {
  return deg / 180.0 * M_PI;
}

float rad2deg(float rad) {
  return rad * 180.0 / M_PI;
}

Quaternion axisAngleToQuat(float angle, Vector3f axis) {
  axis = glm::normalize(axis);

  float sinAngle = sin(angle/2.0);

  return glm::normalize( Quaternion(cos(angle/2.0), axis.x*sinAngle, axis.y*sinAngle, axis.z*sinAngle));
}
