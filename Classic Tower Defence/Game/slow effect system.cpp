//
//  slow effect system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 27/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "slow effect system.hpp"

#include "unit stats component.hpp"
#include "slow effect component.hpp"

void slowEffectSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<UnitStats, SlowEffect>();
  for (const ECS::EntityID entity : view) {
    SlowEffect &effect = view.get<SlowEffect>(entity);
    UnitStats &stats = view.get<UnitStats>(entity);
    stats.moveSpeed *= effect.speedFactor;
    stats.dodge *= effect.speedFactor;
    
    effect.duration -= delta;
    if (effect.duration < 0.0f) {
      reg.remove<SlowEffect>(entity);
    }
  }
}
