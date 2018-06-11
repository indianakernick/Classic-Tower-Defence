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
#include "tower beam anim component.hpp"

void towerBeamRenderingSystem(ECS::Registry &reg, G2D::Section &sec) {
  const auto view = reg.view<
    Position, TowerTarget, TowerSprites, BeamTower, TowerBeamAnim
  >();
  for (const ECS::EntityID entity : view) {
    const TowerSprites sprites = view.get<TowerSprites>(entity);
    if (!sprites.gun.lastFrame()) {
      continue;
    }
    
    const glm::vec2 pos = view.get<Position>(entity).pos + glm::vec2(0.5f);
    const TowerTarget target = view.get<TowerTarget>(entity);
    const glm::vec2 offset = {
      std::cos(target.angle) * 0.5f,
      std::sin(target.angle) * 0.5f
    };
    const TowerBeamAnim anim = view.get<TowerBeamAnim>(entity);
    const Sprite::Sheet &sheet = sec.sheet();
    const Sprite::Rect rect = sheet.getSprite(sprites.projectile + anim.frame);
    const glm::vec2 size = anim.scaleBeam ? glm::vec2(target.dist - 0.5f, 1.0f)
                                          : rect.size() * (sheet.getLength() / 16.0f);
   
    sec.quad();
    sec.depth(Depth::TOWER_BEAM);
    sec.rotTilePos<G2D::Origin::MID_LEFT>(target.angle, pos + offset, size);
    sec.tileTex(rect);
  }
}
