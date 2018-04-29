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

#include "map component.hpp"
#include "unit stats component.hpp"
#include "tower stats component.hpp"
#include "unit dir component.hpp"
#include "towers component.hpp"
#include "map info component.hpp"
#include "position component.hpp"
#include "unit exit distance component.hpp"
#include "map sprites component.hpp"
#include "tower firing anim component.hpp"
#include "unit path component.hpp"
#include "waves component.hpp"
#include "spawner timing component.hpp"
#include "base health component.hpp"
#include "tower timing component.hpp"
#include "tower target component.hpp"
#include "tower upgrades component.hpp"
#include "slow effect component.hpp"
#include "unit sprite component.hpp"
#include "unit death anim component.hpp"
#include "spawner state component.hpp"
#include "tower sprites component.hpp"
#include "unit walk anim component.hpp"
#include "poison effect component.hpp"
#include "sound component.hpp"

using CompList = Utils::TypeList<
  Map,
  UnitStats,
  TowerStats,
  UnitDir,
  Towers,
  MapInfo,
  Position,
  UnitExitDistance,
  MapSprites,
  TowerFiringAnim,
  UnitPath,
  Waves,
  SpawnerTiming,
  BaseHealth,
  TowerTiming,
  TowerTarget,
  TowerUpgrades,
  SlowEffect,
  UnitSprite,
  UnitDeathAnim,
  SpawnerState,
  TowerSprites,
  UnitWalkAnim,
  PoisonEffect,
  Sound
>;

#endif
