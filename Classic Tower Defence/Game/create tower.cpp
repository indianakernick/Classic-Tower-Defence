//
//  create tower.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create tower.hpp"

#include "towers tag.hpp"
#include "base gold tag.hpp"
#include "sound component.hpp"
#include "position component.hpp"
#include "tower gold component.hpp"

ECS::EntityID createTower(
  ECS::Registry &reg,
  const size_t index,
  const glm::ivec2 pos
) {
  const Towers &towers = reg.get<Towers>();
  const TowerProto &tower = towers.at(index);
  auto &gold = reg.get<BaseGold>().gold;
  const auto cost = tower.get<TowerGold>().buy;
  
  if (cost > gold) {
    return ECS::NULL_ENTITY;
  } else {
    gold -= cost;
  }
  
  const ECS::EntityID entity = tower(reg);
  reg.assign<Position>(entity, pos);
  return entity;
}

const DefaultPrototype *getTowerProto(ECS::Registry &reg, const size_t index) {
  const Towers &towers = reg.get<Towers>();
  if (index < towers.size()) {
    return &towers[index];
  } else {
    return nullptr;
  }
}
