#ifndef __CALCULATOR_SCREEN_H__
#define __CALCULATOR_SCREEN_H__

#include "base_screen.h"
#include "../chunk.h"
#include "../opengl_all.h"
#include "../camera.h"
#include "../shader.h"
#include "../input/keyboard.h"
#include "../input/mouse.h"
#include "../scene/player.h"

class CalculatorScreen : public BaseScreen {
  Chunk chunk;
  Shader shader;

  Keyboard keyboard;
  Mouse mouse;

  Player player;


public:
  CalculatorScreen(App& app);

  void beforeFrame();
  void processEvent(SDL_Event& event);
  void update(double dt);
  void render(Camera& cam);
};

#endif
