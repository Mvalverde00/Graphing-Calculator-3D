#include "app.h"

#include <cassert>
#include <iostream>

#include "screens/calculator_screen.h"
#include "math/util.h"

App::App() {
  // Set OpenGL 3.3 as target version.
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  window = SDL_CreateWindow("SDL2 + OpenGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 1200, SDL_WINDOW_OPENGL);
  assert(window);
  context = SDL_GL_CreateContext(window);

  SDL_SetRelativeMouseMode(SDL_TRUE);
  SDL_GL_SetSwapInterval(1); // Enable VSync

  glewInit();
  glViewport(0, 0, 1200, 1200);

  cam = Camera();
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

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    screens.back()->render(cam);
    SDL_GL_SwapWindow(window);
  }

}


int main(int argc, char* argv[]) {
  App app = App();
  app.run();

  return 1;
}
