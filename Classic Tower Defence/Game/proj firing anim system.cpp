//
//  proj firing anim system.cpp
//  Classic Tower Defence
//
//  Created by Indi Kernick on 6/5/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#include "proj firing anim system.hpp"

#include "projectile tower component.hpp"
#include "tower firing anim component.hpp"

void projFiringAnimSystem(ECS::Registry &reg) {
  auto view = reg.view<ProjectileTower, TowerFiringAnim>();
  
  for (const ECS::EntityID entity : view) {
    TowerFiringAnim &anim = view.get<TowerFiringAnim>(entity);
    if (!anim.running) {
      continue;
    }
    
    ++anim.frame;
    if (anim.frame == anim.frames) {
      anim.running = false;
      anim.frame = 0;
    }
  }
}
