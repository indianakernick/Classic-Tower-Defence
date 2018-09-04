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
#include "tower sprites component.hpp"
#include "projectile tower component.hpp"
#include "tower shoot time component.hpp"

namespace {
  void handleAnimEnd(Sprite::Anim &anim, ECS::Registry &reg, const ECS::EntityID entity) {
    if (
      reg.has<ProjectileTower>(entity) ||
      reg.has<AuraTower>(entity) || (
        reg.has<BeamTower>(entity) &&
        reg.get<TowerTarget>(entity).id == entt::null
      )
    ) {
      anim.stop();
    }
  }
}

void firingAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<TowerSprites, TowerShootTime>();
  
  for (const ECS::EntityID entity : view) {
    TowerShootTime &shoot = view.get<TowerShootTime>(entity);
    TowerSprites &sprites = view.get<TowerSprites>(entity);
    
    if (shoot.elapsed < shoot.startTime) {
      sprites.gun.stop();
    } else if (sprites.gun.running()) {
      if (sprites.gun.incrCheck()) {
        handleAnimEnd(sprites.gun, reg, entity);
      }
    } else if (shoot.target) {
      sprites.gun.start();
    }
  }
}
