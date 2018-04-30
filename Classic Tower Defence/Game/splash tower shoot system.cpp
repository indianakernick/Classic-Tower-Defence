//
//  splash tower shoot system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "splash tower shoot system.hpp"

#include <glm/gtx/norm.hpp>
#include "position component.hpp"
#include "unit damage system.hpp"
#include "unit stats component.hpp"
#include "tower target component.hpp"
#include "splash tower component.hpp"
#include "tower firing anim component.hpp"
#include "common tower stats component.hpp"

void slashTowerShootSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerTarget, SplashTower, TowerFiringAnim, CommonTowerStats>();
  auto unitView = reg.view<UnitStats, Position>();
  for (const ECS::EntityID entity : view) {
    const TowerFiringAnim anim = view.get<TowerFiringAnim>(entity);
    if (!anim.firing || anim.frame != 0) {
      continue;
    }
    
    const CommonTowerStats stats = view.get<CommonTowerStats>(entity);
    const ECS::EntityID target = view.get<TowerTarget>(entity).id;
    const glm::vec2 targetPos = reg.get<Position>(target).pos;
    float aoe = view.get<SplashTower>(entity).aoe;
    aoe *= aoe;
    unitDamageSystem(reg, target, stats.damage, stats.armourPiercing);
    
    for (const ECS::EntityID unit : unitView) {
      const glm::vec2 pos = unitView.get<Position>(unit).pos;
      if (glm::distance2(pos, targetPos) < aoe) {
        unitDamageSystem(reg, unit, stats.damage, stats.armourPiercing);
      }
    }
  }
}
