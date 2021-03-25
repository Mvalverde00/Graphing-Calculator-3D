#pragma once

#include "base_screen.h"

// A screen conforming to the interface, but which does nothing.
// Useful for debugging, as we can isolate and ensure it is not the
// screen causing the issues.
class BlankScreen : public BaseScreen {
  public:
    BlankScreen(App& app) : BaseScreen(app) {};

    void beforeFrame() {};
    void processEvent(SDL_Event& event) {};
    void update(double dt) {};
    void render(Camera& cam) {};
};