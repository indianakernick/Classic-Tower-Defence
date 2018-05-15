//
//  tower projectile rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 5/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower projectile rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "tower target component.hpp"
#include "tower sprites component.hpp"
#include "projectile tower component.hpp"
#include "tower firing anim component.hpp"

void towerProjectileRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  const auto view = reg.view<
    Position, TowerTarget, TowerFiringAnim, TowerSprites, ProjectileTower
  >();
  for (const ECS::EntityID entity : view) {
    const TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    if (!anim.started || anim.frame == 0) {
      continue;
    }
    
    const TowerSprites sprites = view.get<TowerSprites>(entity);
    const glm::vec2 pos = view.get<Position>(entity).pos;
    const TowerTarget target = view.get<TowerTarget>(entity);
    const float progress = static_cast<float>(anim.frame) / (anim.frames - 1);
    
    writer.quad();
    writer.depth(Depth::TOWER_PROJ);
    writer.rotTilePos(target.angle, pos + target.vec * progress);
    writer.tileTex(sheet.getSprite(sprites.projectile));
  }
}
