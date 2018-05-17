//
//  splash tower shoot system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "splash damage system.hpp"

#include <glm/gtx/norm.hpp>
#include "position component.hpp"
#include "unit damage system.hpp"
#include <Simpleton/Math/pow.hpp>
#include "unit stats component.hpp"
#include "tower effect component.hpp"
#include "tower target component.hpp"
#include "splash tower component.hpp"
#include "tower shoot time component.hpp"
#include "common tower stats component.hpp"

void splashDamageSystem(ECS::Registry &reg) {
  auto view = reg.view<
    TowerTarget, TowerEffect, SplashTower, TowerShootTime, CommonTowerStats
  >();
  auto unitView = reg.view<Position, UnitStats>();
  for (const ECS::EntityID entity : view) {
    const TowerShootTime shoot = view.get<TowerShootTime>(entity);
    if (shoot.elapsed < shoot.fireTime) {
      continue;
    }
    
    const CommonTowerStats stats = view.get<CommonTowerStats>(entity);
    const TowerTarget target = view.get<TowerTarget>(entity);
    const float aoe = Math::square(view.get<SplashTower>(entity).aoe);
    const TowerEffect effect = view.get<TowerEffect>(entity);
    if (target.id != ECS::NULL_ENTITY) {
      unitDamageSystem(reg, target.id, stats.damage, stats.armourPiercing);
      effect.apply(reg, target.id);
    }
    
    for (const ECS::EntityID unit : unitView) {
      const glm::vec2 pos = unitView.get<Position>(unit).pos;
      if (glm::distance2(pos, target.pos) < aoe) {
        unitDamageSystem(reg, unit, stats.damage, stats.armourPiercing);
        effect.apply(reg, unit);
      }
    }
  }
}
