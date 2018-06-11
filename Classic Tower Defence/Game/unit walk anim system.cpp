//
//  unit walk anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit walk anim system.hpp"

#include "unit sprite component.hpp"

void unitWalkAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<UnitSprite>();
  for (const ECS::EntityID entity : view) {
    view.get(entity).walk.incrRepeat();
  }
}
