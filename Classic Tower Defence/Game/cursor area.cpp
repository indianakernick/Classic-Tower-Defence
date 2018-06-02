//
//  cursor area.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "cursor area.hpp"

#include <Simpleton/Math/rect.hpp>
#include <Simpleton/SDL/mouse pos.hpp>

ECS::EntityID getObjAtPos(ECS::Registry &reg, const glm::vec2 pos) {
  const auto view = reg.view<Math::RectPP<float>>();
  for (const ECS::EntityID entity : view) {
    if (view.get(entity).encloses(pos)) {
      return entity;
    }
  }
  return ECS::NULL_ENTITY;
}

void updateCursor(
  ECS::Registry &reg,
  SDL::SystemCursors &cursors,
  const ECS::EntityID entity
) {
  if (entity == ECS::NULL_ENTITY) {
    cursors.setDefault();
  } else {
    cursors.set(reg.get<SDL_SystemCursor>(entity));
  }
}

InputConsumed handleClick(ECS::Registry &reg, const ECS::EntityID entity) {
  if (entity != ECS::NULL_ENTITY) {
    reg.get<ClickHandler>(entity)();
    return InputConsumed::YES;
  } else {
    return InputConsumed::NO;
  }
}
