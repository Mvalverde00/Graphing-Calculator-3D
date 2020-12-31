#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

#include <glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vectors.h"
#include "util.h"

struct Frustum {
  // Full angle from bottom to top, in radians
  float fovY;
  float aspect;
  float near;
  float far;


  Matrix4f projectionMatrix;

  Frustum();
  Frustum(float near, float far, float left, float right, float bottom, float top) {
    this->fovY = 2.0 * atan(top/near);
    this->aspect = (right - left) / (top - bottom);
    this->near = near;
    this->far = far;

    projectionMatrix = glm::perspective(fovY, aspect, near, far);
  }

  Frustum(float fovY, float aspect, float near, float far) {
    this->fovY = fovY;
    this->aspect = aspect;
    this->near = near;
    this->far = far;

    projectionMatrix = glm::perspective(fovY, aspect, near, far);
  }

};

#endif
