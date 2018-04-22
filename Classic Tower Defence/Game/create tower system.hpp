//
//  create tower system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef create_tower_system_hpp
#define create_tower_system_hpp

#include "towers.hpp"
#include <Simpleton/ECS/registry.hpp>

ECS::EntityID createTower(ECS::Registry &, const Towers &, size_t);

#endif
