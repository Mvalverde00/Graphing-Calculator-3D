#ifndef __CALCULATOR_SCREEN_H__
#define __CALCULATOR_SCREEN_H__

#include "base_screen.h"
#include "../chunk.h"
#include "../opengl_all.h"
#include "../camera.h"
#include "../shader.h"
#include "../mesh.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../scene/player.h"
#include "../chunk_manager.h"

class CalculatorScreen : public BaseScreen {
  ChunkManager chunkManager;
  Chunk chunk;
  Shader shader;
  Shader axesShader;

  Keyboard keyboard;
  Mouse mouse;

  Player player;

  Mesh axes;


public:
  CalculatorScreen(App& app);

  void beforeFrame();
  void processEvent(SDL_Event& event);
  void update(double dt);
  void render(Camera& cam);
};

#endif
