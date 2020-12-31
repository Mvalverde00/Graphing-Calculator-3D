#include "calculator_screen.h"

#include <SDL.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "../app.h"
#include "../opengl_all.h"
#include "../load_shader.h"


CalculatorScreen::CalculatorScreen(App& app) : BaseScreen(app), chunk(-10.0, -10.0, 10.0, 10.0) {
  shader = Shader("shaders/vert.glsl", "shaders/frag.glsl");
  player = Player();
  app.cam.bind(&player);
}

void CalculatorScreen::beforeFrame() {
  mouse.reset();
}

void CalculatorScreen::processEvent(SDL_Event& event) {
  keyboard.processEvent(event);
  mouse.processEvent(event);
}

void CalculatorScreen::update(double dt) {
  player.processInput(keyboard, mouse);
  player.tick(dt);
}

void CalculatorScreen::render(Camera& cam) {
  cam.update();
  shader.use();
  shader.set_matrix4f("projectionView", cam.getProjectViewMatrix());

  chunk.getMesh().bindVAO();
  glDrawElements(GL_TRIANGLES, chunk.getMesh().getIndicesSize(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
