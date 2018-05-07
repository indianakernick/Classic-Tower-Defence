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
#include "unit walk anim component.hpp"

void slowEffectSystem(ECS::Registry &reg, const float delta) {
  auto view = reg.view<UnitStats, SlowEffect, UnitWalkAnim>();
  for (const ECS::EntityID entity : view) {
    SlowEffect &effect = view.get<SlowEffect>(entity);
    UnitStats &stats = view.get<UnitStats>(entity);
    stats.moveSpeed *= effect.speedFactor;
    stats.dodge *= effect.speedFactor;
    
    effect.duration -= delta;
    if (effect.duration < 0.0f) {
      view.get<UnitWalkAnim>(entity).subframes = 1;
      reg.remove<SlowEffect>(entity);
    } else {
      uint32_t &subframes = view.get<UnitWalkAnim>(entity).subframes;
      if (effect.speedFactor == 0.0f) {
        subframes = std::numeric_limits<uint32_t>::max();
      } else {
        subframes = std::nearbyint(1.0f / effect.speedFactor) + 0.001f;
      }
    }
  }
}
