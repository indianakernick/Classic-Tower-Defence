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
#include "unit sprite component.hpp"

void slowEffectSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<UnitStats, SlowEffect, UnitSprite>();
  for (const ECS::EntityID entity : view) {
    SlowEffect &effect = view.get<SlowEffect>(entity);
    UnitStats &stats = view.get<UnitStats>(entity);
    stats.moveSpeed *= effect.speedFactor;
    stats.dodge *= effect.speedFactor;
    
    effect.duration -= delta;
    if (effect.duration < 0.0f) {
      view.get<UnitSprite>(entity).walk.noDelay();
      reg.remove<SlowEffect>(entity);
    } else {
      if (effect.speedFactor == 0.0f) {
        view.get<UnitSprite>(entity).walk.maxDelay();
      } else {
        view.get<UnitSprite>(entity).walk.speed(effect.speedFactor);
      }
    }
  }
}
