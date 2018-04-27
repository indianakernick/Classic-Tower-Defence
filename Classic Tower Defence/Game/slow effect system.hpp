//
//  slow effect system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 27/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef slow_effect_system_hpp
#define slow_effect_system_hpp

#include "slow effect component.hpp"
#include <Simpleton/ECS/registry.hpp>

void slowEffectSystem(ECS::Registry &, float);
void addSlowEffect(ECS::Registry &, ECS::EntityID, SlowEffect);

#endif
