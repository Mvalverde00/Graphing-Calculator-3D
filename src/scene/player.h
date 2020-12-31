#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"

class Player : public Entity {

  /* Although player inherits a quaternion rotation variable from Entity, for
   * the sake of handling mouse input controls it is necessary to have a yaw-pitch
   * representation and convert that intermediary to a quaternion */

  //rotation in horizontal direction
  float yaw;
  // rotation in vertical direction
  float pitch;

public:
  Player();
  Player(Vector3f pos);

  void processInput(Keyboard& keyboard, Mouse& mouse);
  void tick(double dt);

};

#endif
