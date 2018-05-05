//
//  tower beam rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 5/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower beam rendering system.hpp"

#include "position component.hpp"
#include "beam tower component.hpp"
#include "tower target component.hpp"
#include "tower sprites component.hpp"
#include "tower firing anim component.hpp"

void towerBeamRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  const auto view = reg.view<
    Position, TowerTarget, TowerFiringAnim, TowerSprites, BeamTower
  >();
  for (const ECS::EntityID entity : view) {
    if (view.get<TowerFiringAnim>(entity).frame == 0) {
      continue;
    }
    const Sprite::ID sprite = view.get<TowerSprites>(entity).projectile;
    const glm::vec2 pos = view.get<Position>(entity).pos + glm::vec2(0.5f);
    const TowerTarget target = view.get<TowerTarget>(entity);
    const float dist = glm::length(target.vec);
    
    writer.quad();
    writer.depth(0.5f);
    writer.rotTilePos<G2D::Origin::MID_LEFT>(-target.angle, pos, {dist, 1.0f});
    writer.tileTex(sheet.getSprite(sprite));
  }
}
