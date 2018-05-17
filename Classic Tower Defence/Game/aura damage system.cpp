//
//  aura damage system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 16/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "aura damage system.hpp"

#include <glm/gtx/norm.hpp>
#include "position component.hpp"
#include "unit damage system.hpp"
#include "aura tower component.hpp"
#include "unit stats component.hpp"
#include "tower effect component.hpp"
#include "tower shoot time component.hpp"
#include "common tower stats component.hpp"

void auraDamageSystem(ECS::Registry &reg) {
  auto towerView = reg.view<
    Position, AuraTower, TowerEffect, TowerShootTime, CommonTowerStats
  >();
  auto unitView = reg.view<Position, UnitStats>();
  for (const ECS::EntityID tower : towerView) {
    const TowerShootTime shoot = towerView.get<TowerShootTime>(tower);
    if (shoot.elapsed < shoot.fireTime) {
      continue;
    }
    
    const glm::vec2 towerPos = towerView.get<Position>(tower).pos;
    const CommonTowerStats stats = towerView.get<CommonTowerStats>(tower);
    const TowerEffect effect = towerView.get<TowerEffect>(tower);
    const float range2 = stats.range * stats.range;
    
    for (const ECS::EntityID unit : unitView) {
      const glm::vec2 unitPos = unitView.get<Position>(unit).pos;
      if (glm::distance2(towerPos, unitPos) < range2) {
        unitDamageSystem(reg, unit, stats.damage, stats.armourPiercing);
        effect.apply(reg, unit);
      }
    }
  }
}
