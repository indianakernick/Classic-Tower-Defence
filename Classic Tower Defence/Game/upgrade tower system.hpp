//
//  upgrade tower system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef upgrade_tower_system_hpp
#define upgrade_tower_system_hpp

#include <Simpleton/ECS/registry.hpp>

void upgradeTowerFirst(ECS::Registry &, ECS::EntityID);
void upgradeTowerSecond(ECS::Registry &, ECS::EntityID);

#endif
