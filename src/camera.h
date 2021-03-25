#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm.hpp>
#include <Engine/src/math/vectors.h>
#include <Engine/src/math/frustum.h>

class Entity;

class Camera {
  Vector3f pos;
  Quaternion rot;

  Engine::Frustum frustum;

  Matrix4f viewMatrix;
  Matrix4f projectViewMatrix;

  Entity* entity;

public:
  Camera();

  /* Updates the camera to follow the entity it is bound to */
  void update();

  /* Binds the camera to an entity.  This means the camera will follow that entity */
  void bind(Entity* entity);

  /* Unbinds the camera from an entity.  The camera will stop tracking the entity, remaining
   * exactly where it was at the moment it was unbound */
  void unbind();

  /* Returns the currently bound entity. */
  Entity* getBoundEntity();

  /* Allows the camera to be manually translated/rotated, if it is unbound */
  void translate(Vector3f delta);
  void rotate(Quaternion rot);

  /* Rebuilds view and projection matrices using current position and rotation */
  void recreateMatrices();

  Matrix4f& getProjectViewMatrix();

};

#endif
