//
//  tower reset rof system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 15/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower reset rof system.hpp"

#include "tower shoot time component.hpp"

void towerResetRofSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerShootTime>();
  for (const ECS::EntityID entity : view) {
    TowerShootTime &shoot = view.get(entity);
    if (shoot.elapsed >= shoot.fireTime) {
      shoot.elapsed = 0.0f;
    }
  }
}
