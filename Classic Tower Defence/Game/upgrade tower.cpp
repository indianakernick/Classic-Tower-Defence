//
//  upgrade tower.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "upgrade tower.hpp"

#include "towers tag.hpp"
#include "tower upgrades component.hpp"

void upgradeTower(ECS::Registry &reg, const ECS::EntityID entity) {
  const TowerProto *next = reg.get<TowerUpgrades>(entity).next;
  // other code should check whether the tower can be upgraded before calling
  // this function
  assert(next);
  (*next)(reg, entity);
}
