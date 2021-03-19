#include "calculator_screen.h"

#include <SDL.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "../app.h"
#include "../opengl_all.h"
#include "../load_shader.h"


CalculatorScreen::CalculatorScreen(App& app) : BaseScreen(app), chunk(-10.0, -10.0, 10.0, 10.0) {
  shader = Shader("shaders/vert.glsl", "shaders/frag.glsl");
  axesShader = Shader("shaders/colored_vertices.vert", "shaders/colored_vertices.frag");
  player = Player(Vector3f(0.0, 1.0, 0.0));
  app.cam.bind(&player);
	
  // X Y and Z lines
  std::vector<Vector3f> vertices = {Vector3f(-100.0, 0.0, 0.0), Vector3f(100.0, 0.0, 0.0), Vector3f(0.0, -100.0, 0.0), Vector3f(0.0, 100.0, 0.0), Vector3f(0.0, 0.0, -100.0), Vector3f(0.0, 0.0, 100.0)};
  // X = Red, Y = Green, Z = Blue
  std::vector<Vector3f> colors = { Vector3f(1.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0), Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 0.0, 1.0), Vector3f(0.0, 0.0, 1.0) };
  axes = Mesh(vertices);
  axes.addVBO(colors);
}

void CalculatorScreen::beforeFrame() {
  keyboard.beginTick();
  mouse.reset();
}

void CalculatorScreen::processEvent(SDL_Event& event) {
  keyboard.processEvent(event);
  mouse.processEvent(event);
}

void CalculatorScreen::update(double dt) {
  player.processInput(keyboard, mouse);
  player.tick(dt);

  chunkManager.recenter(player.getPos());
}

void CalculatorScreen::render(Camera& cam) {
  cam.update(); // TODO: bad practice, move this somewhere

  shader.use();
  shader.set_matrix4f("projectionView", cam.getProjectViewMatrix());
  for (Chunk* chunk : chunkManager.getVisibleChunks()) {
	  chunk->getMesh().bindVAO();
	  glDrawElements(GL_LINES, chunk->getMesh().getIndicesSize(), GL_UNSIGNED_INT, 0);
  }

  axesShader.use();
  axesShader.set_matrix4f("projectionView", cam.getProjectViewMatrix());
  axes.bindVAO();
  glDrawArrays(GL_LINES, 0, axes.getIndicesSize());
  glBindVertexArray(0);

  glBindVertexArray(0);
}
