//
//  unit death rendering system.hpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef unit_death_rendering_system_hpp
#define unit_death_rendering_system_hpp

#include <Simpleton/ECS/registry.hpp>
#include <Simpleton/Sprite/sheet.hpp>
#include <Simpleton/Graphics 2D/quad writer.hpp>

void unitDeathRenderingSystem(
  ECS::Registry &,
  G2D::QuadWriter &,
  const Sprite::Sheet &
);

#endif
