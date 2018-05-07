//
//  unit health rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 25/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "unit health rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "unit stats component.hpp"

void unitHealthRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  const Sprite::ID healthID = sheet.getIDfromName("health 0");
  const Sprite::ID armourID = sheet.getIDfromName("armour 0");
  const auto view = reg.view<Position, UnitStats>();
  for (const ECS::EntityID entity : view) {
    const UnitStats &stats = view.get<UnitStats>(entity);
    const float maxHealth = stats.proto->get<UnitStats>().health;
    const float maxArmour = stats.proto->get<UnitStats>().armour;
    const glm::vec2 pos = view.get<Position>(entity).pos;
    
    if (maxHealth - stats.health > 1.0f) {
      writer.quad();
      writer.depth(Depth::UNIT_HEALTH);
      writer.tilePos(pos);
      writer.tileTex(sheet.getSprite(
        healthID + std::round(stats.health / maxHealth * 16)
      ));
    }
    
    if (maxArmour - stats.armour > 1.0f) {
      writer.quad();
      writer.depth(Depth::UNIT_HEALTH);
      writer.tilePos(pos);
      writer.tileTex(sheet.getSprite(
        armourID + std::round(stats.armour / maxArmour * 16)
      ));
    }
  }
}
