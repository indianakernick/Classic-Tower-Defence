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
  G2D::Section &sec,
  const ECS::EntityID tower
) {
  const int range = reg.get<CommonTowerStats>(tower).range;
  assert(1 <= range && range <= 32);
  const glm::vec2 pos = reg.get<Position>(tower).pos;
  
  sec.quad();
  sec.depth(0.0f);
  sec.tilePos(
    pos - glm::vec2(range),
    glm::vec2(1 + range * 2)
  );
  sec.tileTex(range - 1);
}
