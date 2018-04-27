//
//  unit effect system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 27/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit effect system.hpp"

#include "unit stats component.hpp"

void unitEffectSystem(ECS::Registry &reg) {
  auto view = reg.view<UnitStats>();
  for (const ECS::EntityID entity : view) {
    UnitStats &stats = view.get(entity);
    const float health = stats.health;
    const float armour = stats.armour;
    *static_cast<UnitStatsBase *>(&stats) = *stats.proto;
    stats.health = health;
    stats.armour = armour;
  }
}
