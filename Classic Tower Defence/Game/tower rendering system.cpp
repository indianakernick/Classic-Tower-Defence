//
//  tower rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower rendering system.hpp"

#include "position component.hpp"
#include "tower target component.hpp"
#include "tower sprites component.hpp"
#include "tower firing anim component.hpp"

void towerRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Unpack::Spritesheet &sheet
) {
  const auto view = reg.view<Position, TowerTarget, TowerFiringAnim, TowerSprites>();
  for (const ECS::EntityID entity : view) {
    const TowerSpritesBase sprites = *view.get<TowerSprites>(entity).proto;
    const Unpack::SpriteID base = sprites.base;
    const Unpack::SpriteID gun = sprites.gun + view.get<TowerFiringAnim>(entity).frame;
    const glm::vec2 pos = view.get<Position>(entity).pos;
    
    writer.quad();
    writer.depth(0.5f);
    writer.tilePos(pos);
    writer.tileTex(sheet.getSprite(base));
    
    writer.quad();
    writer.depth(0.4f);
    writer.rotTilePos(view.get<TowerTarget>(entity).gunAngle, pos);
    writer.tileTex(sheet.getSprite(gun));
  }
}
