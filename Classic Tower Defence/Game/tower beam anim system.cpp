//
//  tower beam anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 5/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "tower beam anim system.hpp"

#include "beam tower component.hpp"
#include "tower target component.hpp"
#include "tower sprites component.hpp"
#include "tower firing anim component.hpp"

void towerBeamAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerSprites, TowerFiringAnim, BeamTower, TowerTarget>();
  for (const ECS::EntityID entity : view) {
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    const Sprite::ID frames = view.get<TowerSprites>(entity).firingFrames;
    
    if (anim.firing) {
      if (anim.frame != frames - 1) {
        ++anim.frame;
      }
      if (view.get<TowerTarget>(entity).id == ECS::NULL_ENTITY) {
        anim.firing = false;
        anim.frame = 0;
      }
    }
  }
}
