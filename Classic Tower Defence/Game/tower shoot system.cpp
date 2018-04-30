//
//  tower shoot system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower shoot system.hpp"

#include "tower shoot component.hpp"
#include "tower timing component.hpp"
#include "tower target component.hpp"
#include "tower firing anim component.hpp"
#include "common tower stats component.hpp"

void towerShootSystem(ECS::Registry &reg) {
  auto view = reg.view<
    TowerShoot, CommonTowerStats, TowerTiming, TowerTarget, TowerFiringAnim
  >();
  
  for (const ECS::EntityID entity : view) {
    const CommonTowerStats &towerStats = view.get<CommonTowerStats>(entity);
    float &timeSinceLastShot = view.get<TowerTiming>(entity).timeSinceLastShot;
    if (timeSinceLastShot < 1.0f / towerStats.rof) {
      continue;
    }
    
    const ECS::EntityID target = view.get<TowerTarget>(entity).id;
    if (target == ECS::NULL_ENTITY) {
      continue;
    }
    
    timeSinceLastShot = 0;
    
    view.get<TowerShoot>(entity).shoot = true;
    
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    anim.frame = 0;
    anim.firing = true;
  }
}
