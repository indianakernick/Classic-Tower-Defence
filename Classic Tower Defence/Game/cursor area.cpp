//
//  cursor area.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "cursor area.hpp"

void CursorArea::init() {
  for (int i = 0; i != SDL_NUM_SYSTEM_CURSORS; ++i) {
    const auto id = static_cast<SDL_SystemCursor>(i);
    cursors.emplace_back(SDL_CreateSystemCursor(id));
  }
}

void CursorArea::set(const SDL_SystemCursor cursor) {
  SDL_SetCursor(cursors.at(cursor).c);
}

void CursorArea::update(const glm::mat3 toMeters) {
  glm::ivec2 mousePos;
  SDL_GetMouseState(&mousePos.x, &mousePos.y);
  SDL_Window *const window = SDL_GetMouseFocus();
  glm::ivec2 windowSize;
  SDL_GetWindowSize(window, &windowSize.x, &windowSize.y);
  
  // converting from pixels to normalized device coordinates to meters
  glm::vec2 pos = mousePos;
  pos /= glm::vec2(windowSize);
  pos *= 2.0f;
  pos -= 1.0f;
  pos.y = -pos.y;
  pos = toMeters * glm::vec3(pos.x, pos.y, 1.0f);
  
  for (const Pair &pair : pairs) {
    if (pair.rect.encloses(pos)) {
      return set(pair.cursor);
    }
  }
  SDL_SetCursor(SDL_GetDefaultCursor());
}

size_t CursorArea::mark(const Rect rect, const SDL_SystemCursor cursor) {
  const size_t id = pairs.size();
  pairs.push_back({rect, cursor});
  return id;
}

CursorArea::Pair &CursorArea::get(const size_t id) {
  return pairs.at(id);
}

void CursorArea::remove(const size_t id) {
  pairs.at(id).rect = {};
}
