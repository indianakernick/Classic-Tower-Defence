//
//  upgrade tower.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "upgrade tower.hpp"

#include "towers component.hpp"
#include "tower upgrades component.hpp"

namespace {
  void upgradeTower(ECS::Registry &reg, const ECS::EntityID entity, const TowerProto *tower) {
    // other code should check whether the tower can be upgraded before calling
    // this function
    assert(tower);
    (*tower)(reg, entity);
  }
}

void upgradeTowerFirst(ECS::Registry &reg, const ECS::EntityID entity) {
  upgradeTower(reg, entity, reg.get<TowerUpgrades>(entity).first);
}

void upgradeTowerSecond(ECS::Registry &reg, const ECS::EntityID entity) {
  upgradeTower(reg, entity, reg.get<TowerUpgrades>(entity).second);
}
