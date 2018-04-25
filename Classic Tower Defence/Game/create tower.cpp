//
//  create tower.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "create tower.hpp"

#include "towers component.hpp"
#include "sound component.hpp"
#include "position component.hpp"
#include "tower timing component.hpp"
#include "tower target component.hpp"
#include "tower firing anim component.hpp"

ECS::EntityID createTower(
  ECS::Registry &reg,
  const size_t index,
  const glm::ivec2 pos
) {
  const Towers &towers = reg.get<Towers>();
  const TowerProto &tower = towers.at(index);
  
  const ECS::EntityID entity = reg.create();
  reg.assign<Position>(entity, pos);
  reg.assign<TowerStats>(entity, &tower.stats);
  reg.assign<TowerSprites>(entity, &tower.sprites);
  reg.assign<TowerUpgrades>(entity, &tower.upgrades);
  reg.assign<TowerTiming>(entity, 0.0f);
  reg.assign<TowerTarget>(entity, 0.0f, ECS::NULL_ENTITY);
  reg.assign<TowerFiringAnim>(entity, uint32_t(0), false);
  reg.assign<Sound>(entity, tower.sound);
  return entity;
}
