//
//  cursor systems.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 19/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "cursor systems.hpp"

#include "basic components.hpp"
#include <Simpleton/SDL/mouse pos.hpp>

ECS::EntityID getObjAtPos(ECS::Registry &reg, const glm::vec2 pos) {
  const auto view = reg.view<Bounds>();
  for (const ECS::EntityID entity : view) {
    if (view.get(entity).encloses(pos)) {
      return entity;
    }
  }
  return entt::null;
}

void updateCursor(
  ECS::Registry &reg,
  SDL::SystemCursors &cursors,
  const ECS::EntityID entity
) {
  if (entity == entt::null) {
    cursors.setDefault();
  } else {
    cursors.set(reg.get<SDL_SystemCursor>(entity));
  }
}

Consumed handleClick(ECS::Registry &reg, const ECS::EntityID entity) {
  if (entity != entt::null) {
    reg.get<ClickHandler>(entity)();
    return Consumed::YES;
  } else {
    return Consumed::NO;
  }
}
