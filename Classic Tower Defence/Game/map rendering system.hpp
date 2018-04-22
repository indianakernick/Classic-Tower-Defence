//
//  map rendering system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef map_rendering_system_hpp
#define map_rendering_system_hpp

#include "map.hpp"
#include "map sprites.hpp"
#include <Simpleton/Unpack/sheet.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

void mapRenderingSystem(
  const Map &,
  G2D::QuadWriter &,
  const Unpack::Spritesheet &,
  MapSprites
);

#endif
