//
//  create tower system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create tower system.hpp"

ECS::EntityID createTower(ECS::Registry &reg, const Towers &towers, const size_t index) {
  const TowerProto &tower = towers.at(index);
  const ECS::EntityID entity = reg.create();
  reg.assign<TowerStats>(entity, &tower.stats);
  reg.assign<TowerSprites>(entity, &tower.sprites);
  reg.assign<TowerUpgrades>(entity, &tower.upgrades);
  return entity;
}
