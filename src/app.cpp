#include "app.h"

#include <cassert>
#include <iostream>

#include "screens/calculator_screen.h"
#include "math/util.h"

App::App() {
  window = SDL_CreateWindow("SDL2 + OpenGL", 0, 0, 800, 800, SDL_WINDOW_OPENGL);
  assert(window);
  context = SDL_GL_CreateContext(window);

  glViewport(0, 0, 800, 800);

  cam = Camera();
  cam.translate(Vector3f(0.0, 0.0, 10.0));
  //cam.rotate(axisAngleToQuat(deg2rad(45.0), Vector3f(0.0, 1.0, 0.0)));

  //SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
  SDL_SetRelativeMouseMode(SDL_TRUE);
}

App::~App() {
  SDL_GL_DeleteContext(context);
  SDL_DestroyWindow(window);
}

void App::run() {
  std::unique_ptr<BaseScreen> screen = std::unique_ptr<BaseScreen>(new CalculatorScreen(*this));
  screens.push_back( std::unique_ptr<BaseScreen>(new CalculatorScreen(*this)) );

  SDL_Event event;
  bool running = true;

  // Setup for fixed-timestep system
  const double UPDATE_TIMESTEP = 1.0 / 30.0;  // 30 ticks per second
  Uint64 performanceFreq = SDL_GetPerformanceFrequency();
  Uint64 prev = SDL_GetPerformanceCounter();
  Uint64 now;
  double accumulator = 0.0;

  while(running) {
    screens.back()->beforeFrame();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }

      screens.back()->processEvent(event);
    }

    now = SDL_GetPerformanceCounter();
    accumulator += (((double)(now - prev))/performanceFreq);
    prev = now;
    while (accumulator >= UPDATE_TIMESTEP) {
      screens.back()->update(UPDATE_TIMESTEP);
      accumulator -= UPDATE_TIMESTEP;
    }

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    screens.back()->render(cam);
    SDL_GL_SwapWindow(window);
  }

}


int main(int argc, char* argv[]) {
  App app = App();
  app.run();
}
