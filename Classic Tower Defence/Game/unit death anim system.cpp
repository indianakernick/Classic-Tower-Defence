//
//  unit death anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit death anim system.hpp"

#include "unit sprite component.hpp"
#include "unit death anim component.hpp"

void unitDeathAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<UnitSprite, UnitDeathAnim>();
  for (const ECS::EntityID entity : view) {
    const uint32_t frames = view.get<UnitSprite>(entity).deathFrames;
    uint32_t &frame = view.get<UnitDeathAnim>(entity).frame;
    ++frame;
    if (frame == frames) {
      reg.destroy(entity);
    }
  }
}
