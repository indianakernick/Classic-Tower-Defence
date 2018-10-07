//
//  stats controller.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 3/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats controller.hpp"

Consumed StatsController::click(const glm::vec2 pos, ECS::Registry &reg) {
  if (view.sellBounds().encloses(pos)) {
    model.sell(reg);
    return Consumed::YES;
  }
  
  if (view.upgradeBounds().encloses(pos)) {
    model.upgrade(reg);
    return Consumed::YES;
  }
  
  return Consumed::NO;
}

Consumed StatsController::hover(const glm::vec2 pos, SDL::SystemCursors &cursors) {
  if (view.sellBounds().encloses(pos)) {
    cursors.set(SDL_SYSTEM_CURSOR_HAND);
    return Consumed::YES;
  }

  if (view.upgradeBounds().encloses(pos)) {
    cursors.set(SDL_SYSTEM_CURSOR_HAND);
    return Consumed::YES;
  }
  
  return Consumed::NO;
}

void StatsController::setRenderState(ECS::Registry &reg) {
  if (model.hasTable()) {
    view.setName(model.getName(reg));
    view.setTable(model.getTable(reg));
    if (model.hasButtons(reg)) {
      view.setButtons(model.getButtons(reg));
    } else {
      view.setNoButtons();
    }
  } else {
    view.clearState();
  }
}

void StatsController::render(G2D::Section &sec, G2D::Text &text) {
  view.render(sec, text);
}
