//
//  tower range rendering system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_range_rendering_system_hpp
#define tower_range_rendering_system_hpp

#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

void towerRangeRenderingSystem(ECS::Registry &, G2D::Section &, ECS::EntityID);

#endif
