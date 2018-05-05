//
//  tower projectile anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 21/4/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower projectile anim system.hpp"

#include "tower sprites component.hpp"
#include "projectile tower component.hpp"
#include "tower firing anim component.hpp"

void towerProjectileAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerSprites, TowerFiringAnim, ProjectileTower>();
  for (const ECS::EntityID entity : view) {
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    if (!anim.firing) {
      continue;
    }
    const Sprite::ID frames = view.get<TowerSprites>(entity).firingFrames;
    
    ++anim.frame;
    if (anim.frame == frames) {
      anim.frame = 0;
      anim.firing = false;
    }
  }
}
