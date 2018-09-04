//
//  turret tower shoot system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "turret damage system.hpp"

#include "unit damage system.hpp"
#include "tower target component.hpp"
#include "turret tower component.hpp"
#include "tower shoot time component.hpp"
#include "common tower stats component.hpp"

void turretDamageSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerTarget, TurretTower, TowerShootTime, CommonTowerStats>();
  for (const ECS::EntityID entity : view) {
    const TowerShootTime shoot = view.get<TowerShootTime>(entity);
    if (shoot.elapsed >= shoot.fireTime) {
      const ECS::EntityID target = view.get<TowerTarget>(entity).id;
      if (target != entt::null) {
        const CommonTowerStats stats = view.get<CommonTowerStats>(entity);
        unitDamageSystem(reg, target, stats.damage, stats.armourPiercing);
      }
    }
  }
}
