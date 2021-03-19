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
  float n; // near
  float f; // far


  Matrix4f projectionMatrix;

  Frustum();
  Frustum(float n, float f, float left, float right, float bottom, float top) {
    this->fovY = 2.0f * atan(top/n);
    this->aspect = (right - left) / (top - bottom);
    this->n = n;
    this->f = f;

    projectionMatrix = glm::perspective(fovY, aspect, n, f);
  }

  Frustum(float fovY, float aspect, float n, float f) {
    this->fovY = fovY;
    this->aspect = aspect;
    this->n = n;
    this->f = f;

    projectionMatrix = glm::perspective(fovY, aspect, n, f);
  }

};

#endif
