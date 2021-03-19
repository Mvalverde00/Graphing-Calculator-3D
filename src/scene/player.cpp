#include "player.h"

#include <glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "../math/util.h"

Player::Player() : Entity() {

};

Player::Player(Vector3f pos) : Entity(pos) {

}

void Player::processInput(Keyboard& keyboard, Mouse& mouse) {
  vel = Vector3f(0, 0, 0);

  if (keyboard.isKeyDown(SDLK_w)) {
    vel.z -= 1.0;
  }
  if (keyboard.isKeyDown(SDLK_s)) {
    vel.z += 1.0;
  }

  if (keyboard.isKeyDown(SDLK_a)) {
    vel.x -= 1.0;
  }
  if (keyboard.isKeyDown(SDLK_d)) {
    vel.x += 1.0;
  }

  if (keyboard.isKeyDown(SDLK_SPACE)) {
      vel.y += 1.0;
  }
  if (keyboard.isKeyDown(SDLK_LSHIFT)) {
      vel.y -= 1.0;
  }

  float norm = glm::length(vel);

  if (norm != 0.0) {
    float playerSpeed = 2.5;
    // sprinting with r
    if (keyboard.isKeyDown(SDLK_r)) {
      playerSpeed *= 5;
    }

    vel = playerSpeed * vel / norm;
  }

  yaw -= mouse.getDx();
  pitch -= mouse.getDy();

  if (pitch > 89.5) {
    pitch = 89.5;
  } else if (pitch < -89.5) {
    pitch = -89.5;
  }

  Quaternion yawRot = axisAngleToQuat(deg2rad(yaw), Vector3f(0.0, 1.0, 0.0));
  vel = Vector3f((yawRot * Vector4f(vel, 1.0)));
  

  rot = yawRot * axisAngleToQuat(deg2rad(pitch), Vector3f(1.0, 0.0, 0.0));
};

void Player::tick(double dt) {
  pos = pos + (float)dt*vel;
  //std::cout << "Player is at " << glm::to_string(pos) << "\n";
}
