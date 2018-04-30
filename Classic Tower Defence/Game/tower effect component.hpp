//
//  tower effect component.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_effect_component_hpp
#define tower_effect_component_hpp

#include <functional>
#include <Simpleton/Data/json.hpp>
#include "slow effect component.hpp"
#include <Simpleton/ECS/registry.hpp>
#include "poison effect component.hpp"

struct TowerEffect {
  std::function<void (ECS::Registry &, ECS::EntityID)> apply;
};

inline void from_json(const json &node, TowerEffect &comp) {
  if (JSON_OPTIONAL(effectNode, node, "SlowEffect")) {
    SlowEffect effect;
    Data::get(effect.speedFactor, *effectNode, "speedFactor");
    Data::get(effect.duration, *effectNode, "duration");
    comp.apply = [effect] (ECS::Registry &reg, const ECS::EntityID entity) {
      reg.accommodate<SlowEffect>(entity, effect);
    };
  } else if (JSON_OPTIONAL(effectNode, node, "PoisonEffect")) {
    PoisonEffect effect;
    Data::get(effect.damageFactor, *effectNode, "damageFactor");
    Data::get(effect.duration, *effectNode, "duration");
    comp.apply = [effect] (ECS::Registry &reg, const ECS::EntityID entity) {
      reg.accommodate<PoisonEffect>(entity, effect);
    };
  }
}

#endif
