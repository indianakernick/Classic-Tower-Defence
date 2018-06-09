//
//  map rendering system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef map_rendering_system_hpp
#define map_rendering_system_hpp

#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

void mapRenderingSystem(ECS::Registry &, G2D::Section &);

#endif
