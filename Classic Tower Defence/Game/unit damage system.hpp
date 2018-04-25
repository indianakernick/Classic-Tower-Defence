//
//  unit damage system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_damage_system_hpp
#define unit_damage_system_hpp

#include <Simpleton/ECS/registry.hpp>

void unitDamageSystem(ECS::Registry &, ECS::EntityID, float, float);

#endif
