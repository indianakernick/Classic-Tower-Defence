//
//  tower beam rendering system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 5/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef tower_beam_rendering_system_hpp
#define tower_beam_rendering_system_hpp

#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Sprite/sheet.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

void towerBeamRenderingSystem(
  ECS::Registry &,
  G2D::QuadWriter &,
  const Sprite::Sheet &
);

#endif
