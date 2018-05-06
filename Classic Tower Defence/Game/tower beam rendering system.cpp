//
//  tower beam rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 5/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower beam rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "beam tower component.hpp"
#include "tower target component.hpp"
#include "tower sprites component.hpp"

void towerBeamRenderingSystem(
  ECS::Registry &reg,
  G2D::QuadWriter &writer,
  const Sprite::Sheet &sheet
) {
  const auto view = reg.view<
    Position, TowerTarget, TowerSprites, BeamTower
  >();
  for (const ECS::EntityID entity : view) {
    if (!view.get<BeamTower>(entity).firing) {
      continue;
    }
    const TowerSprites sprites = view.get<TowerSprites>(entity);
    const glm::vec2 pos = view.get<Position>(entity).pos + glm::vec2(0.5f);
    const TowerTarget target = view.get<TowerTarget>(entity);
    
    writer.quad();
    writer.depth(Depth::TOWER_BEAM);
    writer.rotTilePos<G2D::Origin::MID_LEFT>(
      target.angle, pos, {target.dist, 1.0f}
    );
    writer.tileTex(sheet.getSprite(sprites.projectile));
  }
}
