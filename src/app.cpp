#include "app.h"

#include <cassert>
#include <iostream>
#include <Engine/src/opengl_all.h>
#include <Engine/dep/imgui.h>
#include <Engine/dep/imgui_impl_sdl.h>
#include <Engine/dep/imgui_impl_opengl3.h>

#include "screens/calculator_screen.h"
#include "screens/blank_screen.h"


App::App() : _fpsCounter(1000) {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);

  _window = new Engine::Window("SDL2 + OpenGL", 1200, 1200);
  cam = Camera();

  std::cout << "Initialzed App!\n";
}

App::~App() {
  delete _window;

  std::cout << "Deleted App!\n";
}

void App::run() {
  //std::unique_ptr<BaseScreen> screen = std::unique_ptr<BaseScreen>(new CalculatorScreen(*this));
  screens.push_back( std::unique_ptr<BaseScreen>(new CalculatorScreen(*this)) );
  //screens.push_back(std::unique_ptr<BaseScreen>(new BlankScreen(*this)));

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
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        running = false;
      }

      screens.back()->processEvent(event);
    }

    // Begin new Imgui Frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window->_sdl_window);
    ImGui::NewFrame();

    _fpsCounter.addSample(1.0 / ImGui::GetIO().Framerate);
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
    _fpsCounter.render();
    screens.back()->renderImgui();
    
    // Render ImGUI on top of everything.
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    SDL_GL_SwapWindow(_window->_sdl_window);
  }

}


int main(int argc, char* argv[]) {
  App app = App();
  app.run();

  return 1;
}
