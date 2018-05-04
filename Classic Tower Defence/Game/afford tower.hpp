//
//  afford tower.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 4/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef afford_tower_hpp
#define afford_tower_hpp

#include <Simpleton/ECS/registry.hpp>

bool affordTower(ECS::Registry &, size_t);
bool affordFirstUpgrade(ECS::Registry &, ECS::EntityID);
bool affordSecondUpgrade(ECS::Registry &, ECS::EntityID);

#endif
