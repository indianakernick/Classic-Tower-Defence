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
    if (view.get<UnitSprite>(entity).death.incrStop()) {
      reg.destroy(entity);
    }
  }
}
