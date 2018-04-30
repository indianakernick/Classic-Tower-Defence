//
//  turret tower shoot system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "turret tower shoot system.hpp"

#include "unit damage system.hpp"
#include "tower target component.hpp"
#include "turret tower component.hpp"
#include "tower firing anim component.hpp"
#include "common tower stats component.hpp"

void turretTowerShootSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerTarget, TurretTower, TowerFiringAnim, CommonTowerStats>();
  for (const ECS::EntityID entity : view) {
    const TowerFiringAnim anim = view.get<TowerFiringAnim>(entity);
    if (anim.firing && anim.frame == 0) {
      const ECS::EntityID target = view.get<TowerTarget>(entity).id;
      const CommonTowerStats stats = view.get<CommonTowerStats>(entity);
      unitDamageSystem(reg, target, stats.damage, stats.armourPiercing);
    }
  }
}
