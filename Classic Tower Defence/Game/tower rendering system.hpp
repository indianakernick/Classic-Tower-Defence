//
//  tower rendering system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_rendering_system_hpp
#define tower_rendering_system_hpp

#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Unpack/sheet.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

void towerRenderingSystem(
  ECS::Registry &,
  G2D::QuadWriter &,
  const Unpack::Spritesheet &
);

#endif
