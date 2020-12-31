#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../math/vectors.h"

class Camera;

class Entity {

protected:
  Vector3f pos;
  Vector3f vel;
  Quaternion rot;

public:
  Entity();
  Entity(Vector3f pos);
  ~Entity();

  void tick() {};

  Vector3f& getPos();
  Quaternion& getRot();
};

#endif
