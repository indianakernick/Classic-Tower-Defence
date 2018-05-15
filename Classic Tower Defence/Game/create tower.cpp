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
#include "tower target component.hpp"

ECS::EntityID createTower(
  ECS::Registry &reg,
  const size_t index,
  const glm::ivec2 pos
) {
  const Towers &towers = reg.get<Towers>();
  const TowerProto &tower = towers.at(index);
  
  if (tower.get<TowerGold>().buy > reg.get<BaseGold>().gold) {
    return ECS::NULL_ENTITY;
  }
  
  const ECS::EntityID entity = tower(reg);
  reg.assign<Position>(entity, pos);
  reg.assign<TowerTarget>(entity);
  return entity;
}
