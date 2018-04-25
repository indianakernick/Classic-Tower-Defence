//
//  create tower.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef create_tower_hpp
#define create_tower_hpp

#include <glm/vec2.hpp>
#include <Simpleton/ECS/registry.hpp>

ECS::EntityID createTower(ECS::Registry &, size_t, glm::ivec2);

#endif
