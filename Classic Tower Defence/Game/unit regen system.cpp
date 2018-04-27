//
//  unit regen system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit regen system.hpp"

#include "unit stats component.hpp"

void unitRegenSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<UnitStats>();
  for (const ECS::EntityID entity : view) {
    UnitStats &stats = view.get(entity);
    stats.health = std::min(
      stats.proto->health, stats.health + stats.healthRegen * delta
    );
    stats.armour = std::min(
      stats.proto->armour, stats.armour + stats.armourRegen * delta
    );
  }
}
