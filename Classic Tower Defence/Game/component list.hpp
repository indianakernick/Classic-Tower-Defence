//
//  component list.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 27/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef component_list_hpp
#define component_list_hpp

#include <Simpleton/Utils/type list.hpp>

#include "unit stats component.hpp"
#include "unit dir component.hpp"
#include "position component.hpp"
#include "unit exit distance component.hpp"
#include "tower firing anim component.hpp"
#include "tower effect component.hpp"
#include "tower shoot component.hpp"
#include "unit path component.hpp"
#include "spawner timing component.hpp"
#include "base health component.hpp"
#include "tower timing component.hpp"
#include "common tower stats component.hpp"
#include "tower target component.hpp"
#include "turret tower component.hpp"
#include "tower upgrades component.hpp"
#include "slow effect component.hpp"
#include "unit sprite component.hpp"
#include "unit death anim component.hpp"
#include "spawner state component.hpp"
#include "tower sprites component.hpp"
#include "unit walk anim component.hpp"
#include "splash tower component.hpp"
#include "poison effect component.hpp"
#include "sound component.hpp"

using CompList = Utils::TypeList<
  UnitStats,
  UnitDir,
  Position,
  UnitExitDistance,
  TowerFiringAnim,
  TowerEffect,
  TowerShoot,
  UnitPath,
  SpawnerTiming,
  BaseHealth,
  TowerTiming,
  CommonTowerStats,
  TowerTarget,
  TurretTower,
  TowerUpgrades,
  SlowEffect,
  UnitSprite,
  UnitDeathAnim,
  SpawnerState,
  TowerSprites,
  UnitWalkAnim,
  SplashTower,
  PoisonEffect,
  Sound
>;

#endif
