//
//  stats model.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "stats model.hpp"

#include "create tower.hpp"
#include "preview entity.hpp"
#include "name component.hpp"
#include <experimental/optional>
#include "unit stats component.hpp"
#include "splash tower component.hpp"
#include "common tower stats component.hpp"

void StatsModel::selectTower(ECS::Registry &reg, const int i) {
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
  if (entity != ECS::NULL_ENTITY) {
    return reg.get<Name>(entity).name;
  } else if (proto != nullptr) {
    return proto->get<Name>().name;
  } else {
    // should check hasTable before calling this function
    assert(false);
    return {};
  }
}

namespace {
  StatsModel::Table getUnitTable(const UnitStats &stats) {
    StatsModel::Table table;
    
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
  
  StatsModel::Table getTowerTable(const CommonTowerStats &stats) {
    StatsModel::Table table;
    
    table.push_back({"DAMAGE", stats.damage});
    table.push_back({"DAMAGE RATE", stats.damage * stats.rof});
    table.push_back({"ARMOUR PIERCING", stats.armourPiercing});
    table.push_back({"FIRE RATE", stats.rof});
    table.push_back({"RANGE", stats.range});
    
    return table;
  }
  
  StatsModel::Table getTowerTable(
    const CommonTowerStats &stats,
    const SplashTower &splash
  ) {
    StatsModel::Table table = getTowerTable(stats);
    table.push_back({"AREA OF EFFECT", splash.aoe});
    return table;
  }
}

StatsModel::Table StatsModel::getTable(ECS::Registry &reg) const {
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
  
  // should check hasTable before calling this function
  assert(false);
  return {};
}
