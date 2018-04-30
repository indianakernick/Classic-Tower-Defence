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
#include "tower shoot component.hpp"
#include "tower effect component.hpp"
#include "tower target component.hpp"
#include "splash tower component.hpp"
#include "common tower stats component.hpp"

void splashTowerShootSystem(ECS::Registry &reg) {
  auto view = reg.view<
    TowerTarget, SplashTower, TowerShoot, CommonTowerStats, TowerEffect
  >();
  auto unitView = reg.view<UnitStats, Position>();
  for (const ECS::EntityID entity : view) {
    bool &shoot = view.get<TowerShoot>(entity).shoot;
    if (!shoot) {
      continue;
    }
    shoot = false;
    
    const CommonTowerStats stats = view.get<CommonTowerStats>(entity);
    const ECS::EntityID target = view.get<TowerTarget>(entity).id;
    const glm::vec2 targetPos = reg.get<Position>(target).pos;
    float aoe = view.get<SplashTower>(entity).aoe;
    aoe *= aoe;
    unitDamageSystem(reg, target, stats.damage, stats.armourPiercing);
    const TowerEffect effect = view.get<TowerEffect>(entity);
    effect.apply(reg, target);
    
    for (const ECS::EntityID unit : unitView) {
      const glm::vec2 pos = unitView.get<Position>(unit).pos;
      if (glm::distance2(pos, targetPos) < aoe) {
        unitDamageSystem(reg, unit, stats.damage, stats.armourPiercing);
        effect.apply(reg, unit);
      }
    }
  }
}
