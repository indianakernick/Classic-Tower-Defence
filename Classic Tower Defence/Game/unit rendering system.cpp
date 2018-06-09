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
#include "unit walk anim component.hpp"

void unitRenderingSystem(ECS::Registry &reg, G2D::Section &sec) {
  const auto view = reg.view<Position, UnitDir, UnitSprite, UnitWalkAnim>();
  for (const ECS::EntityID entity : view) {
    const UnitSprite &sprite = view.get<UnitSprite>(entity);
    Sprite::ID id = sprite.sprite;
    id += Grid::toNum(view.get<UnitDir>(entity).dir, sprite.frames);
    id += view.get<UnitWalkAnim>(entity).frame;
    
    sec.quad();
    sec.depth(Depth::UNIT);
    sec.tilePos(view.get<Position>(entity).pos);
    sec.tileTex(id);
  }
}
