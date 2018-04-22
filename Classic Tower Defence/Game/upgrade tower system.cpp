//
//  upgrade tower system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "upgrade tower system.hpp"

#include "towers.hpp"
#include "tower upgrades component.hpp"

namespace {
  TowerUpgradesBase getUpgrades(ECS::Registry &reg, const ECS::EntityID entity) {
    return *reg.get<TowerUpgrades>(entity).proto;
  }
  
  void upgradeTower(ECS::Registry &reg, const ECS::EntityID entity, const TowerProto *tower) {
    // other code should check whether the tower can be upgraded before calling
    // this function
    assert(tower);
    reg.replace<TowerStats>(entity, &tower->stats);
    reg.replace<TowerSprites>(entity, &tower->sprites);
    reg.replace<TowerUpgrades>(entity, &tower->upgrades);
  }
}

void upgradeTowerFirst(ECS::Registry &reg, const ECS::EntityID entity) {
  upgradeTower(reg, entity, getUpgrades(reg, entity).first);
}

void upgradeTowerSecond(ECS::Registry &reg, const ECS::EntityID entity) {
  upgradeTower(reg, entity, getUpgrades(reg, entity).second);
}
