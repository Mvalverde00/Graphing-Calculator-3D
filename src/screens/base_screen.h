#ifndef __BASE_SCREEN_H__
#define __BASE_SCREEN_H__

#include <SDL.h>

#include "../camera.h"

class App;

class BaseScreen {
public:
  App* app;

  BaseScreen(App& app);


  /* Called once at the beginning of every frame. */
  virtual void beforeFrame() = 0;
  /* Called multiple times every frame with every new event */
  virtual void processEvent(SDL_Event& event) = 0;
  /* Fixed-timestep update.  Called as many times as needed per frame, after all the events have been processed */
  virtual void update(double dt) = 0;
  /* Called once per frame after everything else */
  virtual void render(Camera& cam) = 0;
};

#endif
