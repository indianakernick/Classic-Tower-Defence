//
//  game logic.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "game logic.hpp"

#include "load level.hpp"
#include "load towers.hpp"
#include "create level.hpp"
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
}

void GameLogic::update(ECS::Registry &reg, float delta) {
  delta = 0.05f;

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
