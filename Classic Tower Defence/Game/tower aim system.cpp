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

void towerAimSystem(ECS::Registry &reg) {
  auto towers = reg.view<Position, TowerStats, TowerTarget>();
  auto units = reg.view<Position, UnitExitDistance>();
  
  for (const ECS::EntityID tower : towers) {
    const glm::vec2 towerPos = towers.get<Position>(tower).pos;
    const float range = towers.get<TowerStats>(tower).proto->range;
    
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
      target.vec = targetPos - towerPos;
      target.angle = std::atan2(target.vec.y, target.vec.x);
    }
  }
}
