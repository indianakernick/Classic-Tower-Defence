//
//  tower shoot system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower shoot system.hpp"

#include "unit stats component.hpp"
#include "tower stats component.hpp"
#include "tower timing component.hpp"
#include "tower target component.hpp"
#include "tower firing anim component.hpp"

void towerShootSystem(ECS::Registry &registry) {
  auto view = registry.view<TowerStats, TowerTiming, TowerTarget, TowerFiringAnim>();
  
  for (const ECS::EntityID entity : view) {
    const TowerStatsBase &towerStats = *view.get<TowerStats>(entity).proto;
    float &timeSinceLastShot = view.get<TowerTiming>(entity).timeSinceLastShot;
    if (timeSinceLastShot < 1.0f / towerStats.rof) {
      continue;
    }
    
    const ECS::EntityID target = view.get<TowerTarget>(entity).id;
    if (target == ECS::NULL_ENTITY) {
      continue;
    }
    
    registry.get<UnitStats>(target).health -= towerStats.damage;
    timeSinceLastShot = 0;
    
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    anim.frame = 0;
    anim.firing = true;
  }
}
