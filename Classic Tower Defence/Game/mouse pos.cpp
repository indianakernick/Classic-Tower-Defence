//
//  mouse pos.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 20/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "mouse pos.hpp"

#include <SDL2/SDL_mouse.h>

namespace {
  glm::vec2 mousePos(
    const glm::mat3 &toMeters,
    const glm::ivec2 pos,
    const glm::ivec2 size
  ) {
    // converting from pixels to normalized device coordinates to meters
    glm::vec2 p = pos;
    p /= glm::vec2(size);
    p *= 2.0f;
    p -= 1.0f;
    p.y = -p.y;
    p = toMeters * glm::vec3(p.x, p.y, 1.0f);
    return p;
  }
  
  glm::vec2 mousePos(
    const glm::mat3 &toMeters,
    const glm::ivec2 pos,
    const Uint32 windowID
  ) {
    SDL_Window *const window = SDL_GetWindowFromID(windowID);
    assert(window);
    glm::ivec2 size;
    SDL_GetWindowSize(window, &size.x, &size.y);
    return mousePos(toMeters, pos, size);
  }
}

glm::vec2 mousePos(const glm::mat3 &toMeters) {
  glm::ivec2 pos;
  SDL_GetMouseState(&pos.x, &pos.y);
  SDL_Window *const window = SDL_GetMouseFocus();
  glm::ivec2 size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  return mousePos(toMeters, pos, size);
}

glm::vec2 mousePos(
  const glm::mat3 &toMeters,
  const SDL_MouseButtonEvent &event
) {
  return mousePos(toMeters, {event.x, event.y}, event.windowID);
}

glm::vec2 mousePos(
  const glm::mat3 &toMeters,
  const SDL_MouseMotionEvent &event
) {
  return mousePos(toMeters, {event.x, event.y}, event.windowID);
}
