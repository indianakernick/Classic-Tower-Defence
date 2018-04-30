//
//  poison effect system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 27/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "poison effect system.hpp"

#include "unit stats component.hpp"
#include "poison effect component.hpp"

void poisonEffectSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<UnitStats, PoisonEffect>();
  for (const ECS::EntityID entity : view) {
    PoisonEffect &effect = view.get<PoisonEffect>(entity);
    UnitStats &stats = view.get<UnitStats>(entity);
    stats.health -= effect.damageFactor * stats.proto->health * delta;
    
    effect.duration -= delta;
    if (effect.duration < 0.0f) {
      reg.remove<PoisonEffect>(entity);
    }
  }
}
