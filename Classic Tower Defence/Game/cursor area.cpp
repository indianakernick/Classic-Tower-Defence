//
//  cursor area.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "cursor area.hpp"

#include <Simpleton/SDL/mouse pos.hpp>

void CursorArea::init() {
  cursors.load();
}

void CursorArea::update(const glm::mat3 toMeters) {
  const glm::vec2 pos = SDL::mousePos(toMeters);
  for (const Pair &pair : pairs) {
    if (pair.rect.encloses(pos)) {
      return cursors.set(pair.cursor);
    }
  }
  cursors.setDefault();
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
