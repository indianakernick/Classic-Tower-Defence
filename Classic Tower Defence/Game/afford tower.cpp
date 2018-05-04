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

bool affordUpgrade(ECS::Registry &reg, const TowerProto *tower) {
  return tower && tower->get<TowerGold>().buy <= reg.get<BaseGold>().gold;
}

bool affordFirstUpgrade(ECS::Registry &reg, const ECS::EntityID entity) {
  return affordUpgrade(reg, reg.get<TowerUpgrades>(entity).first);
}

bool affordSecondUpgrade(ECS::Registry &reg, const ECS::EntityID entity) {
  return affordUpgrade(reg, reg.get<TowerUpgrades>(entity).second);
}
