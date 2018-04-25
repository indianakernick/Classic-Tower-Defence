//
//  unit damage system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit damage system.hpp"

#include <random>
#include "unit stats component.hpp"

void unitDamageSystem(
  ECS::Registry &reg,
  const ECS::EntityID unit,
  const float damage,
  const float armourPiercing
) {
  static std::mt19937 gen;
  static std::uniform_real_distribution<float> dist;

  UnitStats &stats = reg.get<UnitStats>(unit);
  
  if (dist(gen) <= stats.dodge) {
    return;
  }
  
  const float healthDamage = armourPiercing * damage;
  const float armourDamage = damage - healthDamage;
  const float leftoverDamage = std::max(0.0f, armourDamage - stats.armour);
  stats.armour -= armourDamage - leftoverDamage;
  stats.health -= healthDamage + leftoverDamage;
}
