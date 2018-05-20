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

namespace {
  int resizeEventWatch(void *app, SDL_Event *event) {
    if (event->type == SDL_WINDOWEVENT) {
      if (event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        reinterpret_cast<App *>(app)->mainloop(0);
        return 0;
      }
    }
    return 1;
  }
}

void App::init() {
  PROFILE(App::init);

  {
    PROFILE(Open Window);
    windowLibrary = SDL::makeLibrary(SDL_INIT_EVENTS);
    window = SDL::makeWindow("Classic Tower Defence", 1280, 720);
    renderingContext.initLimitFPS(window.get(), 20);

    renderingContext.preRender();
    renderingContext.postRender();
    
    renderer.init();
  }
  
  audioLib = SDL::makeAudioLibrary({});
  sounds.load();
  
  SDL_PumpEvents();
  
  logic.init(reg);
  view.init(renderer);
  uiView.init(reg, renderer);
  
  SDL_AddEventWatch(resizeEventWatch, this);
}

void App::quit() {
  PROFILE(App::quit);

  audioLib.reset();
  renderer.quit();
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
      uiView.input(reg, e);
    }
  }
  return true;
}

void App::update(const float delta) {
  PROFILE(App::update);
  if (delta != 0.0f) {
    logic.update(reg, delta);
  }
}

void App::render(const float delta) {
  PROFILE(App::render);
  
  if (delta != 0.0f) {
    view.pushSounds(reg, sounds);
    //sounds.play(DupSound::PLAY_LATER);
  }
  
  renderingContext.preRender();
  
  const Cam2D::Params params = {window.aspect(), delta};
  view.updateCam(params);
  uiView.updateCam(params);
  
  if (delta != 0.0f) {
    view.updateAnim(reg, delta);
    uiView.updateAnim(reg, delta);
  }
  
  writer.clear();
  view.render(reg, writer);
  uiView.render(reg, writer);
  writer.render(renderer);
  
  renderingContext.postRender(delta == 0.0f);
}
