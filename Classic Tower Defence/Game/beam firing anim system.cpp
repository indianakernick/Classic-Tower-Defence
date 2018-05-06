//
//  beam firing anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 6/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "beam firing anim system.hpp"

#include "beam tower component.hpp"
#include "tower shoot component.hpp"
#include "tower firing anim component.hpp"

void beamFiringAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<BeamTower, TowerShoot, TowerFiringAnim>();
  
  for (const ECS::EntityID entity : view) {
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    if (!anim.running) {
      continue;
    }
    
    if (anim.frame == anim.frames - 1) {
      const bool canShoot = view.get<TowerShoot>(entity).canShoot;;
      view.get<BeamTower>(entity).firing = canShoot;
      if (!canShoot) {
        anim.frame = 0;
        anim.running = false;
      }
    } else {
      ++anim.frame;
    }
  }
}
