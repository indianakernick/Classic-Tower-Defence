//
//  unit rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 22/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "unit dir component.hpp"
#include "unit sprite component.hpp"

void unitRenderingSystem(ECS::Registry &reg, G2D::Section &sec) {
  const auto view = reg.view<Position, UnitDir, UnitSprite>();
  for (const ECS::EntityID entity : view) {
    sec.quad();
    sec.depth(Depth::UNIT);
    sec.tilePos(view.get<Position>(entity).pos);
    sec.tileTex(view.get<UnitSprite>(entity).walk.sprite(
      view.get<UnitDir>(entity).dir
    ));
  }
}
