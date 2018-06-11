//
//  unit death rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit death rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "unit sprite component.hpp"
#include "unit death anim component.hpp"

void unitDeathRenderingSystem(ECS::Registry &reg, G2D::Section &sec) {
  auto view = reg.view<Position, UnitSprite, UnitDeathAnim>();
  for (const ECS::EntityID entity : view) {
    sec.quad();
    sec.depth(Depth::UNIT_DEATH);
    sec.tilePos(view.get<Position>(entity).pos);
    sec.tileTex(view.get<UnitSprite>(entity).death.sprite());
  }
}
