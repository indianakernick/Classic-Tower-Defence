//
//  tower range rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 30/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower range rendering system.hpp"

#include "position component.hpp"
#include "common tower stats component.hpp"

void towerRangeRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet,
  const ECS::EntityID tower
) {
  const int range = reg.get<CommonTowerStats>(tower).range;
  assert(1 <= range && range <= 32);
  const glm::vec2 pos = reg.get<Position>(tower).pos;
  
  writer.quad();
  writer.depth(0.0f);
  writer.tilePos(
    pos - glm::vec2(range),
    glm::vec2(1 + range * 2)
  );
  writer.tileTex(sheet.getSprite(range - 1));
}
