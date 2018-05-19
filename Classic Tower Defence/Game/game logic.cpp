//
//  game logic.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game logic.hpp"

#include <string>
#include "load level.hpp"
#include "load towers.hpp"
#include "create level.hpp"
#include "create tower.hpp"
#include "create spawner.hpp"
#include "spawner system.hpp"
#include "tower rof system.hpp"
#include "tower aim system.hpp"
#include "unit death system.hpp"
#include "unit regen system.hpp"
#include "unit motion system.hpp"
#include "base damage system.hpp"
#include "firing anim system.hpp"
#include "unit effect system.hpp"
#include "slow effect system.hpp"
#include "aura damage system.hpp"
#include "poison effect system.hpp"
#include "turret damage system.hpp"
#include "splash damage system.hpp"
#include "spawner timing system.hpp"
#include "tower beam anim system.hpp"
#include "tower reset rof system.hpp"

void GameLogic::init(ECS::Registry &reg) {
  createLevel(reg);
  loadTowers(reg);
  loadLevel(reg, 0);
  
  createTower(reg, 0, {10, 4});
  createTower(reg, 1, {3, 5});
  createTower(reg, 2, {6, 5});
  createTower(reg, 3, {6, 2});
  createTower(reg, 4, {8, 8});
  createTower(reg, 5, {10, 7});
  createTower(reg, 6, {3, 2});
  createTower(reg, 7, {15, 9});
  createTower(reg, 8, {3, 8});
  createTower(reg, 9, {5, 8});
  createTower(reg, 10, {12, 7});
  createTower(reg, 11, {13, 3});
}

InputConsumed GameLogic::input(const SDL_Event &) {
  return InputConsumed::NO;
}

void GameLogic::update(ECS::Registry &reg, const float delta) {
  spawnerTimingSystem(reg, delta);
  spawnerSystem(reg);
  
  unitRegenSystem(reg, delta);
  unitEffectSystem(reg);
  slowEffectSystem(reg, delta);
  poisonEffectSystem(reg, delta);
  
  towerAimSystem(reg);
  towerRofSystem(reg, delta);
  firingAnimSystem(reg);
  turretDamageSystem(reg);
  splashDamageSystem(reg);
  auraDamageSystem(reg);
  towerResetRofSystem(reg);
  
  towerBeamAnimSystem(reg);
  
  unitMotionSystem(reg, delta);
  unitDeathSystem(reg);
  
  baseDamageSystem(reg);
}
