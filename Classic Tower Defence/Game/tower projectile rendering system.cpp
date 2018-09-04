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

void towerProjectileRenderingSystem(ECS::Registry &reg, G2D::Section &sec) {
  const auto view = reg.view<
    Position, TowerTarget, TowerSprites, ProjectileTower
  >();
  for (const ECS::EntityID entity : view) {
    const TowerSprites sprites = view.get<TowerSprites>(entity);
    if (sprites.gun.frame() == 0) {
      continue;
    }
    
    const glm::vec2 pos = view.get<Position>(entity).pos;
    const TowerTarget target = view.get<TowerTarget>(entity);
    
    sec.quad();
    sec.depth(Depth::TOWER_PROJ);
    sec.rotTilePos(target.angle, pos + target.vec * sprites.gun.progressLast());
    sec.tileTex(sprites.projectile);
  }
}
