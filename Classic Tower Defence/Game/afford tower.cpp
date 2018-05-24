//
//  afford tower.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 4/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "afford tower.hpp"

#include "towers tag.hpp"
#include "base gold tag.hpp"
#include "tower gold component.hpp"
#include "tower upgrades component.hpp"

bool affordTower(ECS::Registry &reg, const size_t index) {
  const TowerProto &tower = reg.get<Towers>().at(index);
  return tower.get<TowerGold>().buy <= reg.get<BaseGold>().gold;
}

bool affordUpgrade(ECS::Registry &reg, const ECS::EntityID entity) {
  const TowerProto *next = reg.get<TowerUpgrades>(entity).next;
  return next && next->get<TowerGold>().buy <= reg.get<BaseGold>().gold;
}

uint32_t upgradeCost(ECS::Registry &reg, const ECS::EntityID entity) {
  const TowerProto *next = reg.get<TowerUpgrades>(entity).next;
  return next ? next->get<TowerGold>().buy : 0;
}
