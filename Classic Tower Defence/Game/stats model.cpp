//
//  stats model.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats model.hpp"

#include "create tower.hpp"
#include "base gold tag.hpp"
#include "preview entity.hpp"
#include "name component.hpp"
#include <experimental/optional>
#include "tower gold component.hpp"
#include "unit stats component.hpp"
#include "splash tower component.hpp"
#include "tower upgrades component.hpp"
#include "common tower stats component.hpp"

void StatsModel::selectTower(ECS::Registry &reg, const size_t i) {
  entity = ECS::NULL_ENTITY;
  proto = getTowerProto(reg, i * 3);
}

void StatsModel::selectPreview(ECS::Registry &reg) {
  entity = ECS::NULL_ENTITY;
  proto = getPreviewProto(reg);
}

void StatsModel::unselect() {
  entity = ECS::NULL_ENTITY;
  proto = nullptr;
}

bool StatsModel::hasTable() const {
  return entity != ECS::NULL_ENTITY || proto != nullptr;
}

std::string StatsModel::getName(ECS::Registry &reg) const {
  // should check hasTable before calling this function
  assert(hasTable());
  
  if (entity != ECS::NULL_ENTITY) {
    return reg.get<Name>(entity).name;
  } else if (proto != nullptr) {
    return proto->get<Name>().name;
  } else {
    return {};
  }
}

namespace {
  StatsTable getUnitTable(const UnitStats &stats) {
    StatsTable table;
    
    table.push_back({"HEALTH", stats.health});
    table.push_back({"ARMOUR", stats.armour});
    table.push_back({"HEALTH REGEN", stats.healthRegen});
    table.push_back({"ARMOUR REGEN", stats.armourRegen});
    table.push_back({"DODGE", stats.dodge});
    table.push_back({"MOVE SPEED", stats.moveSpeed});
    table.push_back({"GOLD", stats.gold});
    
    return table;
  }
  
  using OptionalSplash = std::experimental::optional<SplashTower>;
  
  StatsTable getTowerTable(const CommonTowerStats &stats) {
    StatsTable table;
    
    table.push_back({"DAMAGE", stats.damage});
    table.push_back({"DAMAGE RATE", stats.damage * stats.rof});
    table.push_back({"ARMOUR PIERCING", stats.armourPiercing});
    table.push_back({"FIRE RATE", stats.rof});
    table.push_back({"RANGE", stats.range});
    
    return table;
  }
  
  StatsTable getTowerTable(
    const CommonTowerStats &stats,
    const SplashTower &splash
  ) {
    StatsTable table = getTowerTable(stats);
    table.push_back({"AREA OF EFFECT", splash.aoe});
    return table;
  }
}

StatsTable StatsModel::getTable(ECS::Registry &reg) const {
  // should check hasTable before calling this function
  assert(hasTable());
  
  if (proto != nullptr) {
    if (proto->has<UnitStats>()) {
      return getUnitTable(proto->get<UnitStats>());
    } else if (proto->has<CommonTowerStats>()) {
      if (proto->has<SplashTower>()) {
        return getTowerTable(proto->get<CommonTowerStats>(), proto->get<SplashTower>());
      } else {
        return getTowerTable(proto->get<CommonTowerStats>());
      }
    }
  } else if (entity != ECS::NULL_ENTITY) {
    if (reg.has<UnitStats>(entity)) {
      return getUnitTable(reg.get<UnitStats>(entity));
    } else if (reg.has<CommonTowerStats>(entity)) {
      if (reg.has<SplashTower>(entity)) {
        return getTowerTable(reg.get<CommonTowerStats>(entity), reg.get<SplashTower>(entity));
      } else {
        return getTowerTable(reg.get<CommonTowerStats>(entity));
      }
    }
  }
  
  return {};
}

bool StatsModel::hasButtons(ECS::Registry &reg) const {
  if (proto != nullptr) {
    return proto->has<CommonTowerStats>();
  } else if (entity != ECS::NULL_ENTITY) {
    return reg.has<CommonTowerStats>(entity);
  } else {
    return false;
  }
}

TowerButtons StatsModel::getButtons(ECS::Registry &reg) const {
  // should check hasButtons before calling this function
  assert(hasButtons(reg));
  
  TowerButtons buttons;
  buttons.afford = false;
  const uint32_t gold = reg.get<BaseGold>().gold;
  
  if (proto != nullptr) {
    buttons.upgrade = 0;
    buttons.sell = 0;
    buttons.buy = proto->get<TowerGold>().buy;
    buttons.afford = buttons.buy <= gold;
  } else if (entity != ECS::NULL_ENTITY) {
    const TowerProto *const next = reg.get<TowerUpgrades>(entity).next;
    if (next) {
      buttons.upgrade = next->get<TowerGold>().buy;
      buttons.afford = buttons.upgrade <= gold;
    } else {
      buttons.upgrade = 0;
    }
    buttons.sell = reg.get<TowerGold>().sell;
    buttons.buy = 0;
  }
  
  return buttons;
}

