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
#include "tower timing system.hpp"
#include "unit regen system.hpp"
#include "unit effect system.hpp"
#include "slow effect system.hpp"
#include "poison effect system.hpp"
#include "tower rof system.hpp"
#include "proj firing anim system.hpp"
#include "beam firing anim system.hpp"
#include "start proj firing anim system.hpp"
#include "start beam firing anim system.hpp"
#include "turret damage system.hpp"
#include "splash damage system.hpp"

void GameLogic::init(ECS::Registry &reg) {
  createLevel(reg);
  loadTowers(reg);
  loadLevel(reg, 0);
  
  //createTower(reg, 0, {11, 4});
  createTower(reg, 5, {11, 7});
  //createTower(reg, 2, {6, 5});
  createTower(reg, 4, {8, 8});
  //createTower(reg, 5, {4, 8});
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
  towerTimingSystem(reg, delta);
  towerRofSystem(reg);
  projFiringAnimSystem(reg);
  beamFiringAnimSystem(reg);
  startProjFiringAnimSystem(reg);
  startBeamFiringAnimSystem(reg);
  turretDamageSystem(reg);
  splashDamageSystem(reg);
  
  unitMotionSystem(reg, delta);
  unitDeathSystem(reg);
  
  baseDamageSystem(reg);
}
