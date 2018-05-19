//
//  firing anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 6/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "firing anim system.hpp"

#include "aura tower component.hpp"
#include "beam tower component.hpp"
#include "tower target component.hpp"
#include "projectile tower component.hpp"
#include "tower shoot time component.hpp"
#include "tower firing anim component.hpp"

namespace {
  void handleAnimEnd(TowerFiringAnim &anim, ECS::Registry &reg, const ECS::EntityID entity) {
    if (reg.has<BeamTower>(entity)) {
      if (reg.get<TowerTarget>(entity).id == ECS::NULL_ENTITY) {
        anim.frame = 0;
        anim.started = false;
      } else {
        anim.frame = anim.frames - 1;
      }
    } else if (reg.has<ProjectileTower>(entity) || reg.has<AuraTower>(entity)) {
      anim.frame = 0;
      anim.started = false;
    }
  }
}

void firingAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerFiringAnim, TowerShootTime>();
  
  for (const ECS::EntityID entity : view) {
    TowerShootTime &shoot = view.get<TowerShootTime>(entity);
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    
    if (shoot.elapsed < shoot.startTime) {
      anim.started = false;
      anim.frame = 0;
    } else if (anim.started) {
      ++anim.frame;
      if (anim.frame == anim.frames) {
        handleAnimEnd(anim, reg, entity);
      }
    } else if (shoot.target) {
      anim.started = true;
      anim.frame = 0;
    }
  }
}
