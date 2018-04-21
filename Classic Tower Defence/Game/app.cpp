//
//  app.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "app.hpp"

#include <Simpleton/Utils/profiler.hpp>

bool App::mainloop(const uint64_t deltaNano) {
  PROFILE(App::mainloop);
  const float deltaSec = deltaNano / 1'000'000'000.0f;
  
  const bool ok = input();
  update(deltaSec);
  render(deltaSec);
  
  return ok;
}

void App::init() {
  PROFILE(App::init);

  {
    PROFILE(Open Window);
    windowLibrary = SDL::makeLibrary(SDL_INIT_EVENTS);
    window = SDL::makeWindow("Classic Tower Defence", 1280, 720);
    renderingContext.initVSync(window.get());
    glEnable(GL_DEPTH_TEST);

    renderingContext.preRender();
    renderingContext.postRender();
  }
  
  SDL_PumpEvents();
}

void App::quit() {
  PROFILE(App::quit);

  renderingContext.quit();
  window.reset();
  windowLibrary.reset();
}

bool App::input() {
  PROFILE(App::input);
  
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      return false;
    } else {
      
    }
  }
  return true;
}

void App::update(const float delta) {
  PROFILE(App::update);
}

void App::render(const float delta) {
  PROFILE(App::render);
  
  renderingContext.preRender();
  const glm::ivec2 windowSize = window.size();
  const float aspect = static_cast<float>(windowSize.x) / windowSize.y;
  
  renderingContext.postRender();
}
