//
//  tower rof system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 6/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower rof system.hpp"

#include "tower target component.hpp"
#include "tower shoot time component.hpp"

void towerRofSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<TowerTarget, TowerShootTime>();
  for (const ECS::EntityID entity : view) {
    TowerShootTime &shoot = view.get<TowerShootTime>(entity);
    
    shoot.target = view.get<TowerTarget>(entity).id != ECS::NULL_ENTITY;
    shoot.elapsed += delta;
    if (!shoot.target && shoot.elapsed > shoot.startTime) {
      shoot.elapsed = shoot.startTime;
    }
  }
}
