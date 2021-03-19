#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "math/util.h"
#include "scene/entity.h"

Camera::Camera() : frustum(0.3, 20.0, -1, 1, -1, 1) {
//Camera::Camera() : frustum(deg2rad(120.0), 16.0/9.0, 0.3, 10.0) {
  rot = Quaternion(1.0, 0.0, 0.0, 0.0);
  pos = Vector3f(0.0, 0.0, 0.0);

  viewMatrix = Matrix4f(1.0);
  projectViewMatrix = frustum.projectionMatrix * viewMatrix;

  entity = NULL;
}

void Camera::translate(Vector3f delta) {
  pos += delta;
  viewMatrix = glm::translate(viewMatrix, -delta);
  projectViewMatrix = frustum.projectionMatrix * viewMatrix;
}

void Camera::rotate(Quaternion rotation) {
  rot = glm::normalize(rotation * rot);
  viewMatrix =  glm::mat4_cast(glm::normalize(glm::inverse(rotation))) * viewMatrix;

  projectViewMatrix = frustum.projectionMatrix * viewMatrix;
}

Matrix4f& Camera::getProjectViewMatrix() {
  return projectViewMatrix;
}

void Camera::recreateMatrices() {
  // Apply rotation then translation
  viewMatrix = glm::mat4_cast(glm::normalize(glm::inverse(rot))) * Matrix4f(1.0);
  viewMatrix = glm::translate(viewMatrix, -pos);

  projectViewMatrix = frustum.projectionMatrix * viewMatrix;
}




void Camera::update() {
  if (entity != NULL) {
    pos = entity->getPos();
    rot = entity->getRot();

    recreateMatrices();
  }
}

void Camera::bind(Entity* entity) {
  this->entity = entity;
}

void Camera::unbind() {
  this->entity = NULL;
}

Entity* Camera::getBoundEntity() {
  return this->entity;
}
