// This file was generated by a python script

#ifndef component_list_hpp
#define component_list_hpp

#include <Simpleton/Type List/type.hpp>

#include "aim tower component.hpp"
#include "aura tower component.hpp"
#include "beam tower component.hpp"
#include "common tower stats component.hpp"
#include "name component.hpp"
#include "poison effect component.hpp"
#include "position component.hpp"
#include "projectile tower component.hpp"
#include "slow effect component.hpp"
#include "sound component.hpp"
#include "splash tower component.hpp"
#include "tower beam anim component.hpp"
#include "tower effect component.hpp"
#include "tower gold component.hpp"
#include "tower shoot time component.hpp"
#include "tower sprites component.hpp"
#include "tower target component.hpp"
#include "tower upgrades component.hpp"
#include "turret tower component.hpp"
#include "unit death anim component.hpp"
#include "unit dir component.hpp"
#include "unit move distance component.hpp"
#include "unit path component.hpp"
#include "unit sprite component.hpp"
#include "unit stats component.hpp"

using CompList = List::Type<
  AimTower,
  AuraTower,
  BeamTower,
  CommonTowerStats,
  Name,
  PoisonEffect,
  Position,
  ProjectileTower,
  SlowEffect,
  Sound,
  SplashTower,
  TowerBeamAnim,
  TowerEffect,
  TowerGold,
  TowerShootTime,
  TowerSprites,
  TowerTarget,
  TowerUpgrades,
  TurretTower,
  UnitDeathAnim,
  UnitDir,
  UnitMoveDistance,
  UnitPath,
  UnitSprite,
  UnitStats
>;

#endif