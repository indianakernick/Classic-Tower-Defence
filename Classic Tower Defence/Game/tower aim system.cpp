//
//  tower aim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower aim system.hpp"

#include <glm/glm.hpp>
#include "position component.hpp"
#include "tower stats component.hpp"
#include "tower target component.hpp"
#include "unit exit distance component.hpp"

void towerAimSystem(ECS::Registry &registry) {
  auto towers = registry.view<Position, TowerStats, TowerTarget>();
  auto units = registry.view<Position, UnitExitDistance>();
  
  for (const ECS::EntityID tower : towers) {
    const glm::vec2 towerPos = towers.get<Position>(tower).pos;
    const float range = towers.get<TowerStats>(tower).range;
    
    float targetExitDist = std::numeric_limits<float>::max();
    glm::vec2 targetPos;
    ECS::EntityID targetUnit = ECS::NULL_ENTITY;
    
    for (const ECS::EntityID unit : units) {
      const glm::vec2 unitPos = units.get<Position>(unit).pos;
      if (glm::distance(towerPos, unitPos) > range) {
        continue;
      }
    
      const float exitDist = units.get<UnitExitDistance>(unit).dist;
      if (exitDist < targetExitDist) {
        targetExitDist = exitDist;
        targetUnit = unit;
        targetPos = unitPos;
      }
    }
    
    TowerTarget &target = towers.get<TowerTarget>(tower);
    target.id = targetUnit;
    if (targetUnit != ECS::NULL_ENTITY) {
      const glm::vec2 gunDir = targetPos - towerPos;
      target.gunAngle = std::atan2(gunDir.y, gunDir.x);
    }
  }
}
