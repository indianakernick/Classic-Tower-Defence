//
//  tower rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 23/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "aim tower component.hpp"
#include "tower target component.hpp"
#include "tower sprites component.hpp"
#include "tower firing anim component.hpp"

void towerRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  const auto view = reg.view<
    Position, AimTower, TowerTarget, TowerFiringAnim, TowerSprites
  >();
  for (const ECS::EntityID entity : view) {
    const TowerSprites sprites = view.get<TowerSprites>(entity);
    const Sprite::ID frame = view.get<TowerFiringAnim>(entity).frame;
    const Sprite::ID gun = sprites.gun + frame;
    const glm::vec2 pos = view.get<Position>(entity).pos;
    const TowerTarget target = view.get<TowerTarget>(entity);
    
    writer.quad();
    writer.depth(Depth::TOWER_BASE);
    writer.tilePos(pos);
    writer.tileTex(sheet.getSprite(sprites.base));
    
    writer.quad();
    writer.depth(Depth::TOWER_GUN);
    writer.rotTilePos(target.angle, pos);
    writer.tileTex(sheet.getSprite(gun));
  }
}
