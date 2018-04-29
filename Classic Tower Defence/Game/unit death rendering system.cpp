//
//  unit death rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 26/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit death rendering system.hpp"

#include "position component.hpp"
#include "unit sprite component.hpp"
#include "unit death anim component.hpp"

void unitDeathRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  auto view = reg.view<Position, UnitSprite, UnitDeathAnim>();
  for (const ECS::EntityID entity : view) {
    Sprite::ID sprite = view.get<UnitSprite>(entity).death;
    sprite += view.get<UnitDeathAnim>(entity).frame;
  
    writer.quad();
    writer.depth(0.0f);
    writer.tilePos(view.get<Position>(entity).pos);
    writer.tileTex(sheet.getSprite(sprite));
  }
}
