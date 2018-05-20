//
//  unit walk anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit walk anim system.hpp"

#include "unit walk anim component.hpp"

void unitWalkAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<UnitWalkAnim>();
  for (const ECS::EntityID entity : view) {
    UnitWalkAnim &anim = view.get(entity);
    ++anim.subframe;
    if (anim.subframe >= anim.subframes) {
      anim.subframe = 0;
      ++anim.frame;
      if (anim.frame >= anim.frames) {
        anim.frame = 0;
      }
    }
  }
}
