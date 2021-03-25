#ifndef __APP_H__
#define __APP_H__

#include <SDL.h>
#include <vector>
#include <memory>
#include <Engine/src/opengl_all.h>
#include <Engine/src/window.h>
#include <Engine/src/fps_counter.h>

#include "screens/base_screen.h"
#include "camera.h"

/*
 * An app controls the window it displays to and the various screens for any possible state
 * of the application (e.g. gameplay, menus, etc.).  It handles events, updates data, and renders.
 */
class App {
  std::vector<std::unique_ptr<BaseScreen>> screens;

public:

  Camera cam;
  Engine::Window* _window;
  Engine::FPSCounter _fpsCounter;

  App();
  ~App();

  void run();

};

#endif
