//
//  tower aura rendering system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 16/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower aura rendering system.hpp"

#include "depth.hpp"
#include "position component.hpp"
#include "aura tower component.hpp"
#include "tower sprites component.hpp"
#include "tower firing anim component.hpp"

void towerAuraRenderingSystem(ECS::Registry &reg, G2D::Section &sec) {
  const auto view = reg.view<
    Position, AuraTower, TowerSprites, TowerFiringAnim
  >();
  for (const ECS::EntityID entity : view) {
    const TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    const glm::vec2 pos = view.get<Position>(entity).pos;
    const TowerSprites sprites = view.get<TowerSprites>(entity);
    
    // towerRenderingSystem doesn't render the base and the gun because
    // aura towers don't have TowerTarget components
    
    sec.quad();
    sec.depth(Depth::TOWER_GUN);
    sec.tilePos(pos);
    sec.tileTex(sprites.gun + anim.frame);
    
    const Sprite::Sheet &sheet = sec.sheet();
    const Sprite::Rect rect = sheet.getSprite(sprites.projectile + anim.frame);
    
    if (!anim.started || anim.frame == 0) {
      continue;
    }
    
    sec.quad();
    sec.depth(Depth::TOWER_AURA);
    const glm::vec2 meterSize = rect.size() * (sheet.getLength() / 16.0f);
    sec.tilePos(pos - (meterSize - 1.0f) / 2.0f, meterSize);
    sec.tileTex(rect);
  }
}
