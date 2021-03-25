#ifndef __CALCULATOR_SCREEN_H__
#define __CALCULATOR_SCREEN_H__

#include "base_screen.h"
#include "../chunk.h"
#include "../camera.h"
#include "../scene/player.h"
#include "../chunk_manager.h"

#include <Engine/src/opengl_all.h>
#include <Engine/src/shader.h>
#include <Engine/src/mesh.h>
#include <Engine/src/input/keyboard.h>
#include <Engine/src/input/mouse.h>


class CalculatorScreen : public BaseScreen {
  ChunkManager chunkManager;
  Engine::Shader shader;
  Engine::Shader axesShader;

  Engine::Keyboard keyboard;
  Engine::Mouse mouse;

  Player player;

  Engine::Mesh axes;


public:
  CalculatorScreen(App& app);

  void beforeFrame();
  void processEvent(SDL_Event& event);
  void update(double dt);
  void render(Camera& cam);
  void renderImgui();
};

#endif
