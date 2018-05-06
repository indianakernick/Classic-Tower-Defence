//
//  game logic.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game logic.hpp"

#include <string>
#include "create level.hpp"
#include "load level.hpp"
#include "load towers.hpp"
#include "create spawner.hpp"
#include "create tower.hpp"
#include "unit motion system.hpp"
#include "unit death system.hpp"
#include "spawner system.hpp"
#include "spawner timing system.hpp"
#include "base damage system.hpp"
#include "tower aim system.hpp"
#include "tower shoot system.hpp"
#include "turret tower shoot system.hpp"
#include "splash tower shoot system.hpp"
#include "tower timing system.hpp"
#include "unit regen system.hpp"
#include "unit effect system.hpp"
#include "slow effect system.hpp"
#include "poison effect system.hpp"

void GameLogic::init(ECS::Registry &reg) {
  createLevel(reg);
  loadTowers(reg);
  loadLevel(reg, 0);
  
  createTower(reg, 0, {11, 4});
  createTower(reg, 1, {11, 7});
  createTower(reg, 2, {6, 5});
  createTower(reg, 3, {8, 8});
  //createTower(reg, 4, {4, 8});
}

bool GameLogic::input(const SDL_Event &) {
  return false;
}

void GameLogic::update(ECS::Registry &reg, const float delta) {
  towerTimingSystem(reg, delta);
  spawnerTimingSystem(reg, delta);
  spawnerSystem(reg);
  
  unitRegenSystem(reg, delta);
  unitEffectSystem(reg);
  slowEffectSystem(reg, delta);
  poisonEffectSystem(reg, delta);
  
  towerAimSystem(reg);
  towerShootSystem(reg);
  turretTowerShootSystem(reg);
  splashTowerShootSystem(reg);
  
  unitMotionSystem(reg, delta);
  unitDeathSystem(reg);
  
  baseDamageSystem(reg);
}
