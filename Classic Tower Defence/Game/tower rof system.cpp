//
//  tower rof system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 6/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower rof system.hpp"

#include "tower shoot component.hpp"
#include "tower timing component.hpp"
#include "tower target component.hpp"
#include "common tower stats component.hpp"

void towerRofSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerShoot, TowerTiming, TowerTarget, CommonTowerStats>();
  for (const ECS::EntityID entity : view) {
    bool &canShoot = view.get<TowerShoot>(entity).canShoot;
    canShoot = true;
    
    if (view.get<TowerTarget>(entity).id == ECS::NULL_ENTITY) {
      canShoot = false;
      continue;
    }
    
    const float lastShot = view.get<TowerTiming>(entity).timeSinceLastShot;
    const float minTime = 1.0f / view.get<CommonTowerStats>(entity).rof;
    
    if (lastShot < minTime) {
      canShoot = false;
    }
  }
}
