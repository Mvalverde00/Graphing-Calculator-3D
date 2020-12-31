#include "entity.h"

Entity::Entity() {
  pos = Vector3f(0.0, 0.0, 0.0);
  vel = Vector3f(0.0, 0.0, 0.0);
  rot = Quaternion(1.0, 0.0, 0.0, 0.0);
}

Entity::Entity(Vector3f pos) {
  this->pos = pos;
  vel = Vector3f(0.0, 0.0, 0.0);
  rot = Quaternion(1.0, 0.0, 0.0, 0.0);
}

Entity::~Entity() {
}

Vector3f& Entity::getPos() {
  return pos;
}
Quaternion& Entity::getRot() {
  return rot;
}
