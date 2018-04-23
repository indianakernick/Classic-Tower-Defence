//
//  tower timing system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower timing system.hpp"

#include "tower timing component.hpp"

void towerTimingSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<TowerTiming>();
  for (const ECS::EntityID entity : view) {
    view.get(entity).timeSinceLastShot += delta;
  }
}
