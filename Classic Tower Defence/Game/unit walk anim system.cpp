//
//  unit walk anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit walk anim system.hpp"

#include "unit sprite component.hpp"
#include "unit walk anim component.hpp"

void unitWalkAnimSystem(ECS::Registry &registry) {
  auto view = registry.view<UnitSprite, UnitWalkAnim>();
  for (const ECS::EntityID entity : view) {
    const uint32_t frames = view.get<UnitSprite>(entity).frames;
    uint32_t &frame = view.get<UnitWalkAnim>(entity).frame;
    ++frame;
    if (frame == frames) {
      frame = 0;
    }
  }
}
